#!/bin/bash

### get version
dist=`grep -E "^NAME=" /etc/os-release | cut -d= -f2|tr -d '"'`
ver=`grep -E "^VERSION_ID=" /etc/os-release | cut -d= -f2|tr -d '"'`

echo "You are on platform $dist $ver"

if [[ ! -f "libJaguarClient.a" ]]; then
    libname="libJaguarClient_${dist}${ver}.a"
    echo "Downloading http://www.jaguardb.com/lib/$libname ..."
    wget http://www.jaguardb.com/lib/$libname
    /bin/mv -f $libname libJaguarClient.a
    echo "Renamed $libname to libJaguarClient.a"
fi

