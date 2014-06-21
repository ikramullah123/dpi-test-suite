dpi-test-suite
--------------

This is test suite used to test fteproxy [1] for CCS 2013 [2].

[1] https://github.com/kpdyer/fteproxy
[2] https://kpdyer.com/publications/ccs2013-fte.pdf

### Ubuntu 
sudo apt-get install tcpflow tcpreplay libglib2.0-dev libpcap-dev libpcre3-dev swig cmake libtool autoconf automake libpcap-dev flex bison file-dev firefox python-pip xvfb
sudo pip install pyvirtualdisplay
sudo pip install selenium

### OSX
- Install XCode 4.3
- Ensure OSX Developer tools path takes priority over MacPorts in .bashrc (i.e. export PATH=/Developer/usr/bin:/opt/local/bin:$PATH)
- Because of a bug in XCode 4.3 [1], execute:
$ sudo ln -s  /Developer/usr/share/autoconf /usr/share

Then execute:
$ sudo port select --set python python27
$ sudo port install swig swig-python

Then install Pyrex:
- Download http://www.cosc.canterbury.ac.nz/greg.ewing/python/Pyrex/
$ sudo python setup.py install

- Then I had to make sure bin/pyrexc in the Pyrex tarball was in my PATH

[1] http://stackoverflow.com/questions/6033989/aclocal-autoconf-reports-missing-m4sugar-m4-on-mac-os-x

