# Fwww 

 Fwww is the repository for fast Web server applications.
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

    ./2_make_release.sh


	The release is a compresses tar file that can be shipped to production
	hosts for deployment of the product.


