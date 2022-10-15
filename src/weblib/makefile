CC = gcc  -w 
CXX = g++ -std=c++11 -w -static -static-libgcc 
  
INCLUDES = -I/usr/local/include -I. 
CXXFLAGS= ${INCLUDES}

all: weblib 

ODIR=../../build/tmp/weblib
OBJS=${ODIR}/webcgi.o ${ODIR}/ssplit.o ${ODIR}/xconfig.o ${ODIR}/xtime.o

LIBDIR=../../build/lib

mkdirobj=@/bin/mkdir -p ${@D}

${ODIR}/%.o:%.cc
	$(mkdirobj)
	$(CXX) ${CXXFLAGS} -c $<  -o $@

${ODIR}/%.o:%.c
	$(mkdirobj)
	$(CC) ${CXXFLAGS} -c $<  -o $@

mkdirlib=@/bin/mkdir -p ${LIBDIR}

weblib:  ${OBJS}
	ar cr libweb.a ${OBJS} 
	$(mkdirlib)
	/bin/mv -f libweb.a ${LIBDIR}

.PHONY: clean
clean:
	/bin/rm -f ${ODIR}/*.o ${LIBDIR}/libweb.a

