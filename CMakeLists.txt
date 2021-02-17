cmake_minimum_required(VERSION 3.16)
project(cxutils LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(cxutils INTERFACE)

# This is just to make this library IDE friendly
target_sources(cxutils INTERFACE include/cxutils/cxutils.hpp include/cxutils/enumerate.hpp include/cxutils/zip.hpp)

target_include_directories(
    cxutils        
    INTERFACE
    $<BUILD_INTERFACE:${CXUTILS_LIB_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

add_executable(testutils ./tests/main.cpp)
target_link_libraries(testutils cxutils)