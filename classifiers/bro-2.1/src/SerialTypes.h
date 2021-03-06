#ifndef serialtypes_h
#define serialtypes_h

// Each serializable class gets a type.
//
// The type enables a form of poor man's type-checking:
//     Bit 0-7:  Number (unique relative to main parent (see below)).
//     Bit 8-12: Main parent class (SER_IS_*)
//     Bit 13:   unused
//     Bit 14:   1 if preference is to keep in cache.
//     Bit 15:   1 if derived from BroObj.

typedef uint16 SerialType;

static const SerialType SER_TYPE_MASK_EXACT = 0x1fff;
static const SerialType SER_TYPE_MASK_PARENT = 0x1f00;
static const SerialType SER_IS_CACHE_STABLE = 0x4000;
static const SerialType SER_IS_BRO_OBJ = 0x8000;

#define SERIAL_CONST(name, val, type) \
	const SerialType SER_ ## name = val | SER_IS_ ## type;

#define SERIAL_CONST2(name) SERIAL_CONST(name, 1, name)

#define SERIAL_IS(name, val) \
	static const SerialType SER_IS_ ## name = val;
#define SERIAL_IS_BO(name, val) \
	static const SerialType SER_IS_ ## name = val | SER_IS_BRO_OBJ;
#define SERIAL_IS_BO_AND_CACHE_STABLE(name, val) \
	static const SerialType SER_IS_ ## name = val | (SER_IS_BRO_OBJ | SER_IS_CACHE_STABLE);

SERIAL_IS_BO(CONNECTION, 0x0100)
SERIAL_IS(TIMER, 0x0200)
SERIAL_IS(TCP_ENDPOINT, 0x0300)
SERIAL_IS_BO(TCP_ANALYZER, 0x0400)
SERIAL_IS_BO(TCP_ENDPOINT_ANALYZER, 0x0500)
SERIAL_IS(TCP_CONTENTS, 0x0600)
SERIAL_IS(REASSEMBLER, 0x0700)
SERIAL_IS_BO(VAL, 0x0800)
SERIAL_IS_BO_AND_CACHE_STABLE(EXPR, 0x0900)
SERIAL_IS_BO_AND_CACHE_STABLE(BRO_TYPE, 0x0a00)
SERIAL_IS_BO_AND_CACHE_STABLE(STMT, 0x0b00)
SERIAL_IS_BO_AND_CACHE_STABLE(ATTRIBUTES, 0x0c00)
SERIAL_IS_BO_AND_CACHE_STABLE(EVENT_HANDLER, 0x0d00)
SERIAL_IS_BO_AND_CACHE_STABLE(BRO_FILE, 0x0e00)
SERIAL_IS_BO_AND_CACHE_STABLE(FUNC, 0x0f00)
SERIAL_IS_BO(ID, 0x1000)
SERIAL_IS(STATE_ACCESS, 0x1100)
SERIAL_IS_BO(CASE, 0x1200)
SERIAL_IS(LOCATION, 0x1300)
SERIAL_IS(RE_MATCHER, 0x1400)

// These are the externally visible types.
const SerialType SER_NONE = 0;

SERIAL_CONST2(BRO_OBJ)

#define SERIAL_CONN(name, val) SERIAL_CONST(name, val, CONNECTION)
SERIAL_CONN(CONNECTION, 1)
SERIAL_CONN(ICMP_ANALYZER, 2)
// We use ICMP_Echo here rather than ICMP_ECHO because the latter gets
// macro expanded :-(.
SERIAL_CONN(ICMP_Echo, 3)
SERIAL_CONN(ICMP_CONTEXT, 4)
SERIAL_CONN(TCP_CONNECTION, 5)
SERIAL_CONN(TCP_CONNECTION_CONTENTS, 6)
SERIAL_CONN(FTP_CONN, 7)
SERIAL_CONN(UDP_CONNECTION, 8)

#define SERIAL_TIMER(name, val) SERIAL_CONST(name, val, TIMER)
SERIAL_TIMER(TIMER, 1)
SERIAL_TIMER(CONNECTION_TIMER, 2)

SERIAL_CONST2(TCP_ENDPOINT)
SERIAL_CONST2(TCP_ANALYZER)
SERIAL_CONST2(TCP_ENDPOINT_ANALYZER)

#define SERIAL_TCP_CONTENTS(name, val) SERIAL_CONST(name, val, TCP_CONTENTS)
SERIAL_TCP_CONTENTS(TCP_CONTENTS, 1)
SERIAL_TCP_CONTENTS(TCP_CONTENT_LINE, 2)
SERIAL_TCP_CONTENTS(TCP_NVT, 3)

#define SERIAL_REASSEMBLER(name, val) SERIAL_CONST(name, val, REASSEMBLER)
SERIAL_REASSEMBLER(REASSEMBLER, 1)
SERIAL_REASSEMBLER(TCP_REASSEMBLER, 2)

#define SERIAL_VAL(name, val) SERIAL_CONST(name, val, VAL)
SERIAL_VAL(VAL, 1)
SERIAL_VAL(INTERVAL_VAL,  2)
SERIAL_VAL(PORT_VAL, 3)
SERIAL_VAL(ADDR_VAL, 4)
SERIAL_VAL(SUBNET_VAL, 5)
SERIAL_VAL(STRING_VAL, 6)
SERIAL_VAL(PATTERN_VAL, 7)
SERIAL_VAL(LIST_VAL, 8)
SERIAL_VAL(TABLE_VAL, 9)
SERIAL_VAL(RECORD_VAL, 10)
SERIAL_VAL(ENUM_VAL, 11)
SERIAL_VAL(VECTOR_VAL, 12)
SERIAL_VAL(MUTABLE_VAL, 13)

#define SERIAL_EXPR(name, val) SERIAL_CONST(name, val, EXPR)
SERIAL_EXPR(EXPR, 1)
SERIAL_EXPR(NAME_EXPR, 2)
SERIAL_EXPR(CONST_EXPR, 3)
SERIAL_EXPR(UNARY_EXPR, 4)
SERIAL_EXPR(BINARY_EXPR, 5)
SERIAL_EXPR(INCR_EXPR, 6)
SERIAL_EXPR(NOT_EXPR, 7)
SERIAL_EXPR(POS_EXPR, 8)
SERIAL_EXPR(NEG_EXPR, 9)
SERIAL_EXPR(ADD_EXPR, 10)
SERIAL_EXPR(SUB_EXPR, 11)
SERIAL_EXPR(TIMES_EXPR, 12)
SERIAL_EXPR(DIVIDE_EXPR, 13)
SERIAL_EXPR(MOD_EXPR, 14)
SERIAL_EXPR(BOOL_EXPR, 15)
SERIAL_EXPR(EQ_EXPR, 16)
SERIAL_EXPR(REL_EXPR, 17)
SERIAL_EXPR(COND_EXPR, 18)
SERIAL_EXPR(REF_EXPR, 19)
SERIAL_EXPR(ASSIGN_EXPR, 20)
SERIAL_EXPR(INDEX_EXPR, 21)
SERIAL_EXPR(FIELD_EXPR, 22)
SERIAL_EXPR(HAS_FIELD_EXPR, 23)
SERIAL_EXPR(RECORD_CONSTRUCTOR_EXPR, 24)
SERIAL_EXPR(FIELD_ASSIGN_EXPR, 25)
// There used to be a SERIAL_EXPR(RECORD_MATCH_EXPR, 26) here
SERIAL_EXPR(ARITH_COERCE_EXPR, 27)
SERIAL_EXPR(RECORD_COERCE_EXPR, 28)
SERIAL_EXPR(FLATTEN_EXPR, 29)
SERIAL_EXPR(SCHEDULE_EXPR, 30)
SERIAL_EXPR(IN_EXPR, 31)
SERIAL_EXPR(CALL_EXPR, 32)
SERIAL_EXPR(EVENT_EXPR, 33)
SERIAL_EXPR(LIST_EXPR, 34)
SERIAL_EXPR(RECORD_ASSIGN_EXPR, 35)
SERIAL_EXPR(ADD_TO_EXPR, 36)
SERIAL_EXPR(REMOVE_FROM_EXPR, 37)
SERIAL_EXPR(SIZE_EXPR, 38)
SERIAL_EXPR(CLONE_EXPR, 39)
SERIAL_EXPR(TABLE_CONSTRUCTOR_EXPR, 40)
SERIAL_EXPR(SET_CONSTRUCTOR_EXPR, 41)
SERIAL_EXPR(VECTOR_CONSTRUCTOR_EXPR, 42)
SERIAL_EXPR(TABLE_COERCE_EXPR, 43)
SERIAL_EXPR(VECTOR_COERCE_EXPR, 44)

#define SERIAL_STMT(name, val) SERIAL_CONST(name, val, STMT)
SERIAL_STMT(STMT, 1)
SERIAL_STMT(EXPR_LIST_STMT, 2)
// There used to be ALARM_STMT (3) here.
SERIAL_STMT(PRINT_STMT, 4)
SERIAL_STMT(EXPR_STMT, 5)
SERIAL_STMT(IF_STMT, 6)
SERIAL_STMT(SWITCH_STMT, 7)
SERIAL_STMT(ADD_STMT, 8)
SERIAL_STMT(DEL_STMT, 9)
SERIAL_STMT(EVENT_STMT, 10)
SERIAL_STMT(FOR_STMT, 11)
SERIAL_STMT(NEXT_STMT, 12)
SERIAL_STMT(BREAK_STMT, 13)
SERIAL_STMT(RETURN_STMT, 14)
SERIAL_STMT(STMT_LIST, 15)
SERIAL_STMT(EVENT_BODY_LIST, 16)
SERIAL_STMT(INIT_STMT, 17)
SERIAL_STMT(NULL_STMT, 18)
SERIAL_STMT(WHEN_STMT, 19)

#define SERIAL_TYPE(name, val) SERIAL_CONST(name, val, BRO_TYPE)
SERIAL_TYPE(BRO_TYPE, 1)
SERIAL_TYPE(TYPE_LIST, 2)
SERIAL_TYPE(INDEX_TYPE, 3)
SERIAL_TYPE(TABLE_TYPE, 4)
SERIAL_TYPE(SET_TYPE, 5)
SERIAL_TYPE(FUNC_TYPE, 6)
SERIAL_TYPE(RECORD_TYPE, 7)
SERIAL_TYPE(SUBNET_TYPE, 8)
SERIAL_TYPE(FILE_TYPE, 9)
SERIAL_TYPE(ENUM_TYPE, 10)
SERIAL_TYPE(VECTOR_TYPE, 11)

SERIAL_CONST2(ATTRIBUTES)
SERIAL_CONST2(EVENT_HANDLER)
SERIAL_CONST2(BRO_FILE)

#define SERIAL_FUNC(name, val) SERIAL_CONST(name, val, FUNC)
SERIAL_FUNC(FUNC, 1)
SERIAL_FUNC(BRO_FUNC, 2)
SERIAL_FUNC(DEBUG_FUNC, 3)
SERIAL_FUNC(BUILTIN_FUNC, 4)

SERIAL_CONST2(ID)
SERIAL_CONST2(STATE_ACCESS)
SERIAL_CONST2(CASE)
SERIAL_CONST2(LOCATION)
SERIAL_CONST2(RE_MATCHER)

#endif
