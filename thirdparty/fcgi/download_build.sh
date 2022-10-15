#!/bin/bash

pd=`pwd -P`

VER="libfcgi-2.4.2"
FILE="${VER}.tar.gz"
DIR="fcgi2-2.4.2"

if [[ -f "$FILE" ]]; then
	echo "$FILE is found, OK"
else
	wget http://sources.buildroot.net/libfcgi/$FILE
fi

if [[ -d "$DIR" ]]; then
	echo "Found $DIR directory, OK"
else
	tar zxf $FILE
fi

if [[ -f "$pd/install_dir/lib/libfcgi.a" ]]; then
	echo "$VER is already built, OK"
	exit 0
fi

echo "Build $VER ..."
date
cd $DIR

./autogen.sh

./configure --prefix=$pd/install_dir 
make
make install

echo "Build $VER done"
date

