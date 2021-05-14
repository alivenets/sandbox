cmake_minimum_required(VERSION 3.12)

project(OrderedJJson)

set(CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)
find_package(OpenSSL 1.1.0 REQUIRED)

add_executable(test-ordered-json main.cpp)

target_link_libraries(test-ordered-json nlohmann_json::nlohmann_json ${OPENSSL_LIBRARIES})