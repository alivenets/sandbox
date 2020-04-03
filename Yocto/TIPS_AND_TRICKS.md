# Yocto tips and tricks

## Adding package in `.bbappend`

To add package in `.bbappend`, use `PACKAGES_append` or `PACKAGES_prepend` variables.

*NOTE*: `PACKAGE_BEFORE_PN` does not work in `.bbappend`