#!/bin/bash

if /bin/ps aux|grep lighttpd |grep bin_dir >/dev/null ; then
    echo "Stopping lighttpd ..."
    if type killall >/dev/null; then
        killall lighttpd
    else
        if type pkill >/dev/null; then
            pkill lighttpd
        fi
    fi
fi

