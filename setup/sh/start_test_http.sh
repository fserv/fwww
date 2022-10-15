#!/bin/bash

arg=$1

OPENSSL_LIB=../../thirdparty/openssl/install_dir/lib64
export LD_LIBRARY_PATH=$OPENSSL_LIB/:$LD_LIBRARY_PATH
echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"

HTTPD=../../thirdparty/lighttpd/install_dir/sbin/lighttpd
CONF=$HOME/fwww/conf_dir/lighttpd.conf

if [[ -f "$CONF" ]]; then
	echo "$CONF is found, OK"
else
	echo "$CONF is not found, exit"
	exit 1
fi

if [[ "x$arg" = "x-f" ]]; then
	./stop_test_http.sh
	sleep 3
fi

echo $HTTPD -f $CONF
$HTTPD -f $CONF

