// See the file "COPYING" in the main distribution directory for copyright.
//
// See ConnSize.h for more extensive comments.


#include "ConnSizeAnalyzer.h"
#include "TCP.h"



ConnSize_Analyzer::ConnSize_Analyzer(Connection* c)
: Analyzer(AnalyzerTag::ConnSize, c)
	{
	}


ConnSize_Analyzer::~ConnSize_Analyzer()
	{
	}

void ConnSize_Analyzer::Init()
	{
	Analyzer::Init();

	orig_bytes = 0;
	orig_pkts = 0;
	resp_bytes = 0;
	resp_pkts = 0;
	}

void ConnSize_Analyzer::Done()
	{
	Analyzer::Done();
	}

void ConnSize_Analyzer::DeliverPacket(int len, const u_char* data, bool is_orig, int seq, const IP_Hdr* ip, int caplen)
	{
	Analyzer::DeliverPacket(len, data, is_orig, seq, ip, caplen);

	if ( is_orig )
		{
		orig_bytes += ip->TotalLen();
		orig_pkts ++;
		}
	else
		{
		resp_bytes += ip->TotalLen();
		resp_pkts ++;
		}
	}

void ConnSize_Analyzer::UpdateConnVal(RecordVal *conn_val)
	{
	// RecordType *connection_type is decleared in NetVar.h
	int orig_endp_idx = connection_type->FieldOffset("orig");
	int resp_endp_idx = connection_type->FieldOffset("resp");
	RecordVal *orig_endp = conn_val->Lookup(orig_endp_idx)->AsRecordVal();
	RecordVal *resp_endp = conn_val->Lookup(resp_endp_idx)->AsRecordVal();

	// endpoint is the RecordType from NetVar.h
	// TODO: or orig_endp->Type()->AsRecordVal()->FieldOffset()
	int pktidx = endpoint->FieldOffset("num_pkts");
	int bytesidx = endpoint->FieldOffset("num_bytes_ip");

	// TODO: error handling?
	orig_endp->Assign(pktidx, new Val(orig_pkts, TYPE_COUNT));
	orig_endp->Assign(bytesidx, new Val(orig_bytes, TYPE_COUNT));
	resp_endp->Assign(pktidx, new Val(resp_pkts, TYPE_COUNT));
	resp_endp->Assign(bytesidx, new Val(resp_bytes, TYPE_COUNT));

	Analyzer::UpdateConnVal(conn_val);
	}


void ConnSize_Analyzer::FlipRoles()
	{
	Analyzer::FlipRoles();
	uint64_t tmp;

	tmp = orig_bytes;
	orig_bytes = resp_bytes;
	resp_bytes = tmp;

	tmp = orig_pkts;
	orig_pkts = resp_pkts;
	resp_pkts = tmp;
	}

