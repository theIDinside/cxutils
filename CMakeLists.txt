cmake_minimum_required(VERSION 3.16)
project(cxutils LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(CXUTILS_LIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
add_library(cxutils INTERFACE)

# This is just to make this library IDE friendly
target_sources(cxutils INTERFACE include/cxutils/cxutils.hpp include/cxutils/enumerate.hpp include/cxutils/zip.hpp include/cxutils/transform.hpp)

target_include_directories(
    cxutils        
    INTERFACE
    $<BUILD_INTERFACE:${CXUTILS_LIB_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_include_directories(cxutils INTERFACE ./include)

add_executable(testutils ./tests/main.cpp)
target_link_libraries(testutils cxutils)
