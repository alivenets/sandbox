# CMake policies depend on `cmake_minimum_required`

For older versions (<=3.10) some compatibility policies may be disabled. So, if there is an error with `CMP_*` policy, check minimum required version.

# Libraries link interface

ALWAYS specify library link interface in `target_link_libraries` (PRIVATE, PUBLIC, INTERFACE). Then there will be no issues when one module defines default linkage, and another - explicit linkage.