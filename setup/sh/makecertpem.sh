######################################################################################3
##
## Script to create a self-signed certificate PEM file
##
######################################################################################3
#!/bin/bash

CountryCode="US"
State="California"
Location="San Jose"
Organization="MyCompany"
OrganizationUnit="It Department"
CommonName="mycompany.com"

export LD_LIBRARY_PATH=/usr/local/openssl_3.0.5/lib64
OPENSSL_PATH=/usr/local/openssl_3.0.5

## create key and csr
# KEY_TYPE="rsa:4096"
#KEY_TYPE="ed25519"
KEY_TYPE="rsa:4096"
echo
echo "create domain.tmp.key and domain.tmp.csr ..."
subject="/C=$CountryCode/ST=$State/L=$Location/O=$Organization/OU=$OrganizationUnit/CN=$CommonName"
${OPENSSL_PATH}/bin/openssl req -new -newkey ${KEY_TYPE} -nodes \
    -keyout domain.tmp.key -out domain.tmp.csr \
	-subj "$subject"

# sign
echo "Self-sign the domain.tmp.csr with domain.tmp.key ..."
${OPENSSL_PATH}/bin/openssl x509 -req -days 3650 -in domain.tmp.csr -signkey domain.tmp.key -out domain.tmp.crt

# combine
echo "combine domain.tmp.key and domain.tmp.crt into selfsignedcert.pem ..."
cat domain.tmp.key domain.tmp.crt > selfsignedcert.pem
chmod 600 selfsignedcert.pem

chmod 600 domain.tmp.key
chmod 600 domain.tmp.csr
chmod 600 domain.tmp.crt
/bin/mkdir -p tmpout
/bin/mv -f domain.tmp.key domain.tmp.csr domain.tmp.crt tmpout/
