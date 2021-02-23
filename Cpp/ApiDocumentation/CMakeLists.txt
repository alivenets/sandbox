cmake_minimum_required(VERSION 3.0.2)

project(TestApiDocumentation)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(ApiDocumentation)

add_api_documentation_target(TARGET_NAME api-doc PROJECT_NAME "${PROJECT_NAME}" SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/api-doc")

add_executable(TestApiDoc main.cpp ${geoclue_PROXY_SOURCES})
