#!/bin/bash

####################################################################
##  Usage:   ./2_make_release.sh  <version>
##
##  Example: ./2_make_release.sh  1.0.0
##
####################################################################

pd=`pwd -P`

version=$1

if [[ "x$version" = "x" ]]; then
	echo "Please provide a version for the release"
	echo "$0  <version>"
	echo "$0  1.0"
	exit 1
fi


if [[ -d "release/fwww_$version/bin_dir" ]]; then
	/bin/rm -rf release/fwww_$version
fi

if [[ -f "release/fwww-${version}.tar.gz" ]]; then
	/bin/rm -f release/fwww-${version}.tar.gz
fi

mkdir -p release/fwww_$version/bin_dir
mkdir -p release/fwww_$version/conf_dir/conf.d
mkdir -p release/fwww_$version/htdocs
mkdir -p release/fwww_$version/lib_dir/openssl
mkdir -p release/fwww_$version/lib_dir/fcgi
mkdir -p release/fwww_$version/lib_dir/lighttpd

if [[ -f "$HOME/fwww/bin_dir/fwww" ]]; then
	echo "Found $HOME/fwww/bin_dir/fwww, OK"
else
	echo "Cannot find $HOME/fwww/bin_dir/fwww, exit"
	exit 1
fi

/bin/cp -f setup/sh/install.sh  release/fwww_$version
/bin/cp -f build/bin/fwww release/fwww_$version/bin_dir/
/bin/cp -f thirdparty/lighttpd/install_dir/sbin/*  release/fwww_$version/bin_dir/
/bin/cp -f setup/sh/setup_lighttpd_conf_dir.sh  release/fwww_$version/bin_dir/
/bin/cp -f setup/sh/selfsignedcert.pem  release/fwww_$version/bin_dir/
/bin/cp -f setup/sh/makecertpem.sh  release/fwww_$version/bin_dir/
/bin/cp -f setup/sh/start_prod_http.sh  release/fwww_$version/bin_dir/
/bin/cp -f setup/sh/stop_prod_http.sh  release/fwww_$version/bin_dir/

/bin/cp -f setup/conf_dir/lighttpd.conf.template  release/fwww_$version/conf_dir/
/bin/cp -rf setup/conf_dir/* release/fwww_$version/conf_dir/
/bin/cp -rf htdocs release/fwww_$version/

/bin/cp -rf thirdparty/openssl/install_dir/lib64/lib*.a release/fwww_$version/lib_dir/openssl/
/bin/cp -rf thirdparty/openssl/install_dir/lib64/lib*so* release/fwww_$version/lib_dir/openssl/

/bin/cp -rf thirdparty/fcgi/install_dir/lib/libfcgi* release/fwww_$version/lib_dir/fcgi/

/bin/cp -rf thirdparty/lighttpd/install_dir/lib/* release/fwww_$version/lib_dir/lighttpd/


/bin/rm -f release/fwww_$version/conf_dir/lighttpd.conf
/bin/rm -f release/fwww_$version/conf_dir/conf.d/fastcgi.conf

cd release
tar zcf fwww-${version}.tar.gz fwww_$version

echo "Release file is in release/fwww-${version}.tar.gz"
echo

