# Binary optimization

macro(append_flags FLAGS)
	set(_FLAGS ${FLAGS} ${ARGN})
	list(APPEND AGGR_FLAGS ${_FLAGS})
endmacro()

function(join_list VALUES OUTPUT)
	string (REPLACE ";" " " _TMP_STR "${VALUES}")
	set(${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

# Add optimization and stripping flags
append_flags(-Os -s)

# Tune for specific architecture
#append_flags(-mtune=corei7)

#Optimize using function and data sections
#append_flags(-ffunction-sections -fdata-sections -Wl,--gc-sections)

# Miscellaneous optimizations
#append_flags(-fno-unroll-loops -fno-inline-small-functions -finline-functions-called-once)

if (CXX EQUAL "clang++")
  list(APPEND COMPILER_FLAGS -flto -fwhole-program-vtables)

  list(APPEND COMPILER_FLAGS -fvectorize)
else()

# Disable RTTI
#list(APPEND COMPILER_FLAGS -fno-rtti)

endif()

if(COMPILER_FLAGS)
append_flags(${COMPILER_FLAGS})
endif()

# Enable LTO
append_flags(-flto)

# Optimize static object usage
add_definitions(-DREFACTOR_STATIC_OBJS)

join_list("${AGGR_FLAGS}" AGGR_FLAGS)

set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${AGGR_FLAGS}")

message("CMAKE_CXX_FLAGS_MINSIZEREL = ${CMAKE_CXX_FLAGS_MINSIZEREL}")

set(ALL_TARGET_FILES $<TARGET_FILE:AudioManager>)
set(ALL_TARGETS AudioManagerCore AudioManagerUtilities AudioManager)

add_custom_target(strip
	COMMAND /usr/bin/strip --strip-all --remove-section=.comment --remove-section=.note ${ALL_TARGET_FILES}
	COMMAND /usr/bin/du -cbDh ${ALL_TARGET_FILES}
	DEPENDS ${ALL_TARGETS}
	COMMENT "Run strip, remove additional sections"
)

add_custom_command(OUTPUT sectionsize.stamp 
	COMMAND /usr/bin/size ${ALL_TARGET_FILES}
)

add_custom_command(OUTPUT filesize.stamp 
	COMMAND /usr/bin/du -cbDh ${ALL_TARGET_FILES}
)

add_custom_target(binsize ALL
	DEPENDS sectionsize.stamp filesize.stamp
)
