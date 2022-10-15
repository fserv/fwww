#!/bin/sh

pd=`pwd -P`

VER="openssl-3.0.5"
FILE="${VER}.tar.gz"

if [[ -f "$FILE" ]]; then
	echo "File $FILE already downloaded, OK"
else
	echo "Download $FILE ... "
	wget https://www.openssl.org/source/$FILE --no-check-certificate
fi

if [[ -d "$VER" ]]; then
	echo "Directory $VER already exists, OK"
else
	tar zxf $FILE
fi

if [[ -f "$pd/install_dir/bin/openssl" ]]; then
	echo "openssl is already built, OK"
else
	echo "Build $VER ..."
	date
	cd $VER
	./Configure --prefix=$pd/install_dir
	#./Configure --prefix=$pd/install_dir -static
	make 
	make install
	date
	echo "Build $VER is done"
fi


