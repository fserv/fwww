#!/bin/sh

pd=`pwd -P`


echo "Download and build libfcgi ..."
date
cd $pd/fcgi
./download_build.sh
date
echo "Build fcgi done"

echo "Download and build openssl ..."
date
cd $pd/openssl
./download_build.sh
date
echo "Build openssl done"

echo

echo "Download and build lighttpd ..."
cd $pd/lighttpd
./download_build_shared_objects.sh
./download_build.sh
date
echo "Build lighttpd done"


