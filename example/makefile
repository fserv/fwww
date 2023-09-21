CC = gcc  -w 
CXX = g++ -g -std=c++11 -w -static -static-libgcc -static-libstdc++ 
  
INCLUDES = -I/usr/local/include -I../src/weblib -I.  -Iinclude -I../thirdparty/fcgi/install_dir/include
CXXFLAGS= ${INCLUDES} 

LIBDIR=../build/lib
BINDIR=../build/bin

all: setup fwww

FASTLIBS= ${LIBDIR}/libweb.a \
    ../thirdparty/fcgi/install_dir/lib/libfcgi.a

STDCPPLIB=/usr/lib/gcc/x86_64-linux-gnu/11/libstdc++.a
THREADLIB=/usr/lib/x86_64-linux-gnu/libpthread.a


ODIR = ../build/tmp/private_jaguar_restfull
OBJS=${ODIR}/main.o

mkdirobj=@/bin/mkdir -p ${@D}
${ODIR}/%.o:%.cc
	$(mkdirobj)
	$(CXX) ${CXXFLAGS} -c $<  -o $@

mkdirbin=@/bin/mkdir -p ${BINDIR}

setup:
	mkdir -p lib && cd lib && ./download_jaguarlib.sh

fwww:  $(FASTLIBS) ${OBJS}
	$(CXX) -o $@ ${OBJS} ${FASTLIBS} lib/libJaguarClient.a  $(THREADLIB)
	$(mkdirbin)
	/bin/mv -f $@ ${BINDIR}

.PHONY: clean
clean:
	/bin/rm -f ${ODIR}/*.o
