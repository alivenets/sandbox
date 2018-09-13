
function(generate_stub filePrefix xmlFile)
    set(PROXY_SOURCES
	    generated/${filePrefix}_proxy.h
	    generated/${filePrefix}_proxy.cpp
    )

    set(STUB_SOURCES
	    generated/${filePrefix}_stub.h
	    generated/${filePrefix}_stub.cpp
    )
    set(COMMON_SOURCES
	    generated/${filePrefix}_common.h
	    generated/${filePrefix}_common.cpp
    )

    set(ALL_SOURCES ${COMMON_SOURCES} ${PROXY_SOURCES} ${STUB_SOURCES})

    add_custom_command(OUTPUT ${ALL_SOURCES}
                       COMMAND mkdir -p ${CMAKE_BINARY_DIR}/generated
                       COMMAND gdbus-codegen-glibmm --generate-cpp-code=${CMAKE_BINARY_DIR}/generated/${filePrefix} ${xmlFile}
                       DEPENDS ${xmlFile}
                      )

    set(${filePrefix}_PROXY_SOURCES ${COMMON_SOURCES} ${PROXY_SOURCES} PARENT_SCOPE)
    set(${filePrefix}_STUB_SOURCES ${COMMON_SOURCES} ${STUB_SOURCES} PARENT_SCOPE)
endfunction()
