cmake_minimum_required(VERSION 3.16)
project(cxutils LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(CXUTILS_LIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
add_library(cxutils INTERFACE)

# This is just to make this library IDE friendly
target_sources(cxutils INTERFACE
        include/cxutils/cxutils.hpp
        include/cxutils/enumerate.hpp
        include/cxutils/zip.hpp
        include/cxutils/transform.hpp
        include/cxutils/logging.hpp)

target_include_directories(
        cxutils
        INTERFACE
        $<BUILD_INTERFACE:${CXUTILS_LIB_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)
target_include_directories(cxutils INTERFACE ./include)

add_executable(transform_test tests/testtransform.cpp)
target_link_libraries(transform_test cxutils)

add_executable(enumerate_test ./tests/testenumerate.cpp)
target_link_libraries(enumerate_test cxutils)

add_executable(zip_test ./tests/testzip.cpp)
target_link_libraries(zip_test cxutils)

add_executable(log_test ./tests/testlog.cpp)
target_link_libraries(log_test cxutils)
