#!/bin/bash

FWWWHOME="$HOME/fwww"

cd bin_dir

./setup_lighttpd_conf_dir.sh

/bin/cp -rf ../lib_dir $FWWWHOME/

/bin/cp -f fwww lighttpd lighttpd-angel \
   start_prod_http.sh stop_prod_http.sh makecertpem.sh \
   $FWWWHOME/bin_dir


cd $FWWWHOME/bin_dir
./start_prod_http.sh -f
echo "Web server fwww is installed and started"

