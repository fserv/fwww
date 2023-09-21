#!/bin/bash

##################################################################
##
##  Usage:    ./start_prod_http.sh
##  Usage:    ./start_prod_http.sh -f
##
##################################################################

arg=$1

FWWWHOME="$HOME/fwww"

OPENSSL_LIB=$FWWWHOME/lib_dir/openssl
LIGHTTPD_LIB=$FWWWHOME/lib_dir/lighttpd
FCGI_LIB=$FWWWHOME/lib_dir/fcgi

export LD_LIBRARY_PATH=$OPENSSL_LIB:$LIGHTTPD_LIB:$FCGI_LIB:$LD_LIBRARY_PATH

HTTPD=$FWWWHOME/bin_dir/lighttpd
CONF=$FWWWHOME/conf_dir/lighttpd.conf

if [[ -f "$CONF" ]]; then
	echo "$CONF is found, OK"
else
	echo "$CONF is not found, exit"
	exit 1
fi

if [[ "x$arg" = "x-f" ]]; then
	./stop_prod_http.sh
	sleep 3
fi

echo $HTTPD -f $CONF
$HTTPD -f $CONF

