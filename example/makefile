CC = gcc  -w 
CXX = g++ -std=c++11 -w -static -static-libgcc 
  
INCLUDES = -I/usr/local/include -I../src/weblib -I. 
CXXFLAGS= ${INCLUDES}

LIBDIR=../build/lib
BINDIR=../build/bin

all: fwww

FASTLIBS= \
	${LIBDIR}/libweb.a \
    ../thirdparty/fcgi/install_dir/lib/libfcgi.a

SHARELIBS=  -lpthread -ldl

ODIR = ../build/tmp/example
OBJS=${ODIR}/main.o

mkdirobj=@/bin/mkdir -p ${@D}
${ODIR}/%.o:%.cc
	$(mkdirobj)
	$(CXX) ${CXXFLAGS} -c $<  -o $@

mkdirbin=@/bin/mkdir -p ${BINDIR}
fwww:  $(FASTLIBS) ${OBJS}
	$(CXX) -o $@ ${OBJS} ${FASTLIBS} ${SHARELIBS}
	$(mkdirbin)
	/bin/mv -f $@ ${BINDIR}

.PHONY: clean
clean:
	/bin/rm -f ${ODIR}/*.o
