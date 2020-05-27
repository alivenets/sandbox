# CMake policies depend on `cmake_minimum_required`

For older versions (<=3.10) some compatibility policies may be disabled. So, if there is an error with `CMP_*` policy, check minimum required version.

# Libraries link interface

ALWAYS specify library link interface in `target_link_libraries` (PRIVATE, PUBLIC, INTERFACE). Then there will be no issues when one module defines default linkage, and another - explicit linkage.

# How to work link libraries to target outside of target directory

Sometimes,if there is a need to update link dependencies outside of target directory, `target_link_libraries` does not work.
```
  Attempt to add link library "--coverage" to target "mytarget" which is not built in this directory.
```

But there is a way to work around it:
```
    get_property(link_flags TARGET mytarget PROPERTY LINK_LIBRARIES)
    list(APPEND link_flags --coverage)
    set_property(TARGET mytarget PROPERTY LINK_LIBRARIES ${link_flags})
```
