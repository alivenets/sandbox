DESCRIPTION = "Classes Without Boilerplate"
HOMEPAGE = "http://www.attrs.org/"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=d4ab25949a73fe7d4fdee93bcbdbf8ff"

SRC_URI[md5sum] = "4ec003c49360853cf935113d1ae56151"
SRC_URI[sha256sum] = "80203177723e36f3bbe15aa8553da6e80d47bfe53647220ccaa9ad7a5e473ccc"

inherit pypi

RDEPENDS_${PN}_class-target += " \
    ${PYTHON_PN}-crypt \
    ${PYTHON_PN}-ctypes \
"

BBCLASSEXTEND = "native nativesdk"
