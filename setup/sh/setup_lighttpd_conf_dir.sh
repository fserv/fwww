#!/bin/bash

### Configurable settings. Users may customize below settings. 
INSTALL_DIR="$HOME/fwww"  # Installation directory of fwww
HTTP_PORT=8080            # Web server http listening port
HTTPS_PORT=4433           # Web server https listening port


### Run as user and group names.
RUNAS_USER_NAME=`id -un`  # lighttpd runs as own user name
RUNAS_GROUP_NAME=`id -gn` # lighttpd runs as own group name

### SSL certificate file. Default is a self-signed cert file
HTTPS_PEM_FILE="$INSTALL_DIR/conf_dir/selfsignedcert.pem"

### Unix socket between lighttpd and persistent fcgi process
FASTCGI_UNIX_SOCKET="$INSTALL_DIR/home_dir/sockets/fastcgiunix.socket"

### create required directories
/bin/mkdir -p $INSTALL_DIR/server_root/cache_dir
/bin/mkdir -p $INSTALL_DIR/conf_dir/conf.d
/bin/mkdir -p $INSTALL_DIR/log_root
/bin/mkdir -p $INSTALL_DIR/state_dir
/bin/mkdir -p $INSTALL_DIR/home_dir/sockets
/bin/mkdir -p $INSTALL_DIR/bin_dir
/bin/mkdir -p $INSTALL_DIR/htdocs
/bin/chown -R ${RUNAS_USER_NAMAME}.${RUNAS_GROUP_NAME} $INSTALL_DIR
/bin/cp -f  ../conf_dir/conf.d/* $INSTALL_DIR/conf_dir/conf.d/

### run sed to generate real config files
sed -e "s|INSTALL_DIR|$INSTALL_DIR|" \
    -e "s|HTTP_PORT|$HTTP_PORT|g" \
    -e "s|HTTPS_PORT|$HTTPS_PORT|g" \
    -e "s|RUNAS_USER_NAME|$RUNAS_USER_NAMAME|g" \
    -e "s|RUNAS_GROUP_NAME|$RUNAS_GROUP_NAME|g" \
    -e "s|HTTPS_PEM_FILE|$HTTPS_PEM_FILE|g" \
	../conf_dir/lighttpd.conf.template > ../conf_dir/lighttpd.conf

sed -e "s|INSTALL_DIR|$INSTALL_DIR|" \
    -e "s|FASTCGI_UNIX_SOCKET|$FASTCGI_UNIX_SOCKET|g" \
	../conf_dir/conf.d/fastcgi.conf.template > ../conf_dir/conf.d/fastcgi.conf

### copy config files
/bin/cp -f ../conf_dir/lighttpd.conf $INSTALL_DIR/conf_dir/
/bin/cp -f ../conf_dir/conf.d/fastcgi.conf $INSTALL_DIR/conf_dir/conf.d/

### The packaged selfsignedcert.pem is a simple self-signed PEM file.
### You may want to re-create the file for your own organization by
## execuing the following script which will require your domain name
## other information:
if [[ ! -f "selfsignedcert.pem" ]]; then
	./makecertpem.sh
fi


### copy the PEM file to proper place
/bin/cp -f selfsignedcert.pem ${HTTPS_PEM_FILE}
chmod 600 $HTTPS_PEM_FILE


### display messages
echo "Files are created in $INSTALL_DIR"
/bin/ls --color -lrth $INSTALL_DIR
echo
echo "$INSTALL_DIR/log_root"
/bin/ls --color -lrth $INSTALL_DIR/log_root
echo

echo "Config files and directories are created in ${INSTALL_DIR} successfully"

