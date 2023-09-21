# fwww 

 fwww is the repository for fast Web server applications.
 It is based on C++ for fast Web project development, release, and deployment.
 In fwww, the light-weight and fast Web server lighttpd serves user requests,
 which are handed over to C++/C fastcgi processes. The C++/C fastcgi processes
 connect to the back-end JaguarDB for data reads and writes.
 The back-end JaguarDB is a highly scalable distributed NoSQL database, developed
 with C++/C. It is a fast NoSQL datastore to manage time-series and location data.


## For Development

	Run the following script to set up development environment:

	./1_setup_development.sh


## For Release

	After development and testing, developers can make a release:

    ./2_make_release.sh  <VERSION>


	The release is a compresses tar file that can be shipped to production
	hosts for deployment of the product.


## For Operation

   After you make the release, you will have a tar file such as:

       release/fwww_Ubuntu_22.04-3.3.6.tar.gz

    Copy this file to your target node and unpack it:

       $ tar zxf fwww_Ubuntu_22.04-3.3.6.tar.gz
       $ cd fwww_Ubuntu_22.04-3.3.6
       $ ./install.sh

    Please note that your target node must have the same Linux release as
    you development node. That is, if you develop fwww project on Ubuntu 22.04, then 
    you should deploy it on Ubuntu 22.04 platform.


### Pre-compiled Package

    The author of the fwww project has compiled a binary on Ubuntu 22.04 and the tar file
    is uploaded to:

        http://www.jaguardb.com/download/fwww_Ubuntu_22.04-3.3.6.tar.gz

    This package takes http requests and connects to jaguar vector database to fetch data
    from the database. The source code is in the example directory under this project.
    Developers can copy the code to another directory and build your customized C++ application server
    saving data and searching data with a vector database.


