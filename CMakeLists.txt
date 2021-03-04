cmake_minimum_required(VERSION 3.16)
project(cxutils LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
include(cmake/CustomFunctions.cmake)
set(CXUTILS_LIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

set(LibSources
        include/cxutils/cxutils.hpp
        include/cxutils/enumerate.hpp
        include/cxutils/zip.hpp
        include/cxutils/transform.hpp
        include/cxutils/logging.hpp)

SetupLibrary(NAME cxutils
        CXX20 True
        TYPE INTERFACE
        SOURCES ${LibSources}
        INCLUDE_DIRS ./include)

# add_library(cxutils INTERFACE)
# This is just to make this library IDE friendly
# target_sources(cxutils INTERFACE include/cxutils/cxutils.hpp include/cxutils/enumerate.hpp include/cxutils/zip.hpp include/cxutils/transform.hpp include/cxutils/logging.hpp)
# target_include_directories(cxutils INTERFACE $<BUILD_INTERFACE:${CXUTILS_LIB_INCLUDE_DIR}> $<INSTALL_INTERFACE:include>)
# target_include_directories(cxutils INTERFACE ./include)

set(CLANG_FLAGS -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op
        -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wlifetime)

set(GCC_FLAGS ${CLANG_FLAGS})
set(MSVC_FLAGS /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message("You are using CLANG. Setting CLANG flags: ${CLANG_FLAGS}")
    target_compile_options(cxutils INTERFACE ${CLANG_FLAGS})
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("You are using GCC. Setting GCC flags: ${GCC_FLAGS}")
    target_compile_options(cxutils INTERFACE ${GCC_FLAGS})
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("You are using MSVC. Setting MSVC flags: ${MSVC_FLAGS}")
    target_compile_options(cxutils INTERFACE ${MSVC_FLAGS})
endif()

SetupExecutable(NAME transform_test
        CXX20 True
        SOURCES tests/testtransform.cpp
        DEPENDENCIES cxutils)

SetupExecutable(NAME enumerate_test
        CXX20 True
        SOURCES tests/testenumerate.cpp
        DEPENDENCIES cxutils)

SetupExecutable(NAME zip_test
        CXX20 True
        SOURCES tests/testzip.cpp
        DEPENDENCIES cxutils)

SetupExecutable(NAME log_test
        CXX20 True
        SOURCES tests/testlog.cpp
        DEPENDENCIES cxutils)