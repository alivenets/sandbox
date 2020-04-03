#!/bin/sh -e

filename=$1
output_filename=$2

if [ -z $filename -o -z $output_filename ]; then
    echo "Usage: $0 <PKCS12 certificate filename> <output filename>"
    exit 1
fi

if [ ! -e $filename ]; then
    echo "ERROR: $filename does not exist"
    exit 1
fi

priv_key_filename="tmp-private-key.key"
cert_filename="tmp-cert.crt"

if [ -e $priv_key_filename -o -e $cert_filename ]; then
    echo "ERROR: cannot write temporary files: file exists"
    exit 1
fi

# Generate key file
openssl pkcs12 -in $filename -nocerts -out $priv_key_filename -nodes

# Generate cert file
openssl pkcs12 -in $filename -clcerts -nokeys -out $cert_filename

cat $priv_key_filename $cert_filename > $output_filename

rm -f $priv_key_filename || true
rm -f $cert_filename || true
