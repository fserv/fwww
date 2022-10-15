#!/bin/bash

pid=`/bin/ps -aux|grep -v grep|grep lighttpd 2>/dev/null|awk '{print $2}'`
if [[ "x$pid" = "x" ]]; then
	echo "lighttpd not running, OK"
	exit 0
else
	echo "Found lighttpd [$pid], OK"
fi

kill -TERM $pid 

