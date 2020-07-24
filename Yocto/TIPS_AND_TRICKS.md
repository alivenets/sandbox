# Yocto tips and tricks

## Adding package in `.bbappend`

To add package in `.bbappend`, use `PACKAGES_append` or `PACKAGES_prepend` variables.

*NOTE*: `PACKAGE_BEFORE_PN` does not work in `.bbappend`

## `HOSTTOOLS`

If Yocto says that some tool is not found, but installed, adding it to `HOSTTOOLS` may help.

## `OEHasPackage` vs `OERequiresPackage`

OEHasPackage runs the test if the package is present, and silently skips it if the package is absent.
The tests should fail if there is a missing package or other problem.
Eventually, rather use a OERequiresPackage, which will produce a specific missing package failure.
