find_package(Doxygen REQUIRED)

function(add_api_documentation_target)
    set(options)
    set(oneValueArgs TARGET_NAME PROJECT_NAME SOURCE_DIR OUTPUT_DIR)
    set(multiValueArgs)
    cmake_parse_arguments(API_DOC "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

    if (NOT API_DOC_TARGET_NAME)
        message(FATAL_ERROR "TARGET_NAME undefined!")
    endif()

    if (NOT API_DOC_SOURCE_DIR)
        message(FATAL_ERROR "SOURCE_DIR undefined!")
    endif()

    # Prepare doxygen configuration file
    set(API_DOC_PROJECT_NAME ${PROJECT_NAME})
    get_filename_component(DOXYGEN_FILE_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
    configure_file(${DOXYGEN_FILE_DIR}/doxygen.cfg.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg @ONLY)

    add_custom_target(
        ${API_DOC_TARGET_NAME}
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
        COMMENT "Building API documentation using doxygen"
        BYPRODUCTS ${API_DOC_OUTPUT_DIR}
    )

endfunction()

