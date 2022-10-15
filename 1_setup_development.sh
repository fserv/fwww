#!/bin/sh

### Required software to develop fwww
# g++ and make
if type g++
then
	echo "g++ is found, OK"
else
	echo "g++ is not found, please install g++"
	exit 1
fi

if type make
then
	echo "make is found, OK"
else
	echo "make is not found, please install make"
	exit 1
fi


### start to install and build thirdparty packages
pd=`pwd -P`

echo "Install thirdparty software packages ..."
./setup_thirdparty_packages.sh

echo

### setup web server
cd $pd/setup/sh
./setup_lighttpd_conf_dir.sh


### start to build our library 
echo "Build library ..."
cd $pd/src/weblib
make

echo

### make a simple work directory
echo "Make a directory myproj for my first project ..."
cd $pd
mkdir -p myproj
/bin/cp -f example/* myproj/
cd $pd/myproj
make
cd $pd
/bin/cp -f build/bin/fwww $HOME/fwww/bin_dir/
echo "Basic program is build/bin/fwww"
echo

### start http server
echo "Starting web server ..."
cd $pd/setup/sh
./start_test_http.sh -f
echo

### show how to use
echo "You can try open the following URLs:"
echo
echo "    https://<this_host_IP>:4433/fwww/"
echo "    http://<this_host_IP>:8080/fwww/"
echo
echo "Example 1:  curl -k  https://localhost:4433/fwww/"
echo
echo "Example 2:  curl     http://localhost:8080/fwww/"
