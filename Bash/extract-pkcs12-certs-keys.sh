#!/bin/sh -e

# Extract all required certificates from PKCS12 to PEM
#  - Docker-compliant format (.key - private key, .cert - client certificate, -ca.crt - CA certificate)
#  - Git-compliant format
#  - CURL-compliant format (-clcerts.pem - unprotected private key and client certificate)

filename=$1
prefix=$2

usage() {
    echo "$0 <PKCS12 filepath> <prefix>"
    echo "  <PKCS12 filepath> - path to PKCS12 certificate bundle file"
    echo "  <prefix> - prefix to generated filenames"
}

[ ! -e $filename ] && echo "ERROR: $filename does not exist" && usage && exit 1
[ -z $prefix ] && echo "ERROR: prefix is empty" && usage && exit 1

priv_key_filename="${prefix}.key"
cert_filename="${prefix}.cert"
ca_cert_filename="${prefix}-ca.crt"
clcerts_filename="${prefix}-clcerts.pem"

if [ -e $priv_key_filename -o -e $cert_filename -o -e $ca_cert_filename -o -e $clcerts_filename ]; then
    echo "ERROR: cannot write certificate files: file exists"
    exit 1
fi

# Extract key to key file
openssl pkcs12 -in $filename -nocerts -out $priv_key_filename -nodes

# Extract certificate to file
openssl pkcs12 -in $filename -clcerts -nokeys -out $cert_filename

# Extract CA certificate to file
openssl pkcs12 -in $filename -cacerts -nokeys -out $ca_cert_filename

# Create certificate file for CURL
cat $priv_key_filename $cert_filename > $clcerts_filename
