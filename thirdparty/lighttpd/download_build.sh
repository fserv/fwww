#!/bin/bash

pd=`pwd -P`
OPENSSL_DIR=$pd/../openssl/openssl-3.0.5
OPENSSL_INSTALL_DIR=$pd/../openssl/install_dir

if [[ ! -d "${OPENSSL_DIR}" ]]; then
	echo "${OPENSSL_DIR} is not found in ../openssl/, please install openssl_3.0.5 first"
	exit 1
fi

VER="lighttpd-1.4.67"
FILE="${VER}.tar.gz"
if [[ ! -f "$FILE" ]]; then
	wget https://download.lighttpd.net/lighttpd/releases-1.4.x/$FILE --no-check-certificate
else
	echo "$FILE is already downloaded, OK"
fi

if [[ -d "$VER" ]]; then
	echo "Found $VER, OK"
else
	tar zxf $FILE
fi

if [[ -f "$pd/install_dir/sbin/lighttpd" ]]; then
	echo "Lighttpd is already built, OK"
	exit 0
fi

echo "Build lighttpd ... "
date
cd $VER

./configure \
    --prefix=$pd/install_dir \
    --with-openssl \
    --with-openssl-includes=${OPENSSL_INSTALL_DIR}/include \
    --with-openssl-libs=${OPENSSL_INSTALL_DIR}/lib64 

make

LOBJS=`/bin/ls lighttpd-*.o |grep -v angel|tr '\n' ' '`
gcc -o lighttpd ${LOBJS} ls-hpack/lighttpd-lshpack.o \
	${OPENSSL_INSTALL_DIR}/lib64/libcrypto.a -lpcre2-8 -ldl

make install
date

echo
echo "Lighttpd files are built in $pd/install_dir"
echo
