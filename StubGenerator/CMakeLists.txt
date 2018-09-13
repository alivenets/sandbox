cmake_minimum_required(VERSION 3.0.2)

project(TestStubGenerator)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(PkgConfig REQUIRED)

pkg_check_modules(Giomm REQUIRED giomm-2.4)
pkg_check_modules(Glibmm REQUIRED glibmm-2.4)

include(GenerateStub)


generate_stub(geoclue "${CMAKE_SOURCE_DIR}/org.freedesktop.GeoClue2.Agent.xml")

add_executable(Test main.cpp ${geoclue_PROXY_SOURCES})
target_link_libraries(Test
    ${Giomm_LIBRARIES}
    ${Glibmm_LIBRARIES}
)

include_directories(${Glibmm_INCLUDE_DIRS})
include_directories(${Giomm_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR}/generated)
