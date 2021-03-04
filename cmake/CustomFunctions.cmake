include(CMakeParseArguments)

function(SET_CXX_20 REQUIRED_ARG)
    set_target_properties(${REQUIRED_ARG} PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED True
            CXX_EXTENSIONS FALSE)
endfunction()

function(SetupLibrary)
    cmake_parse_arguments(
            PARSED_ARGS # prefix of output variables
            "CXX20" # list of names of the boolean arguments (only defined ones will be true)
            "NAME;TYPE" # list of names of mono-valued arguments
            "SOURCES;INCLUDE_DIRS" # list of names of multi-valued arguments (output variables are lists)
            ${ARGN} # arguments of the function to parse, here we take the all original ones
    )
    # note: if it remains unparsed arguments, here, they can be found in variable PARSED_ARGS_UNPARSED_ARGUMENTS
    if(NOT PARSED_ARGS_NAME)
        message(FATAL_ERROR "You must provide a name")
    endif(NOT PARSED_ARGS_NAME)
    message("Provided sources are:")

    string(COMPARE EQUAL "${PARSED_ARGS_TYPE}" "INTERFACE" _cmp)
    if (_cmp)
        message("Library is of interface type")
        add_library(${PARSED_ARGS_NAME} INTERFACE)
        target_sources(${PARSED_ARGS_NAME} INTERFACE ${PARSED_ARGS_SOURCES})
        target_include_directories(${PARSED_ARGS_NAME} INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
        if(PARSED_ARGS_INCLUDE_DIRS)
            foreach(dir in ${PARSED_ARGS_INCLUDE_DIRS})
                target_include_directories(${PARSED_ARGS_NAME} INTERFACE ${dir})
            endforeach()
        endif()
        if(PARSED_ARGS_CXX20)
            message("CXX standard set to c++20 for library target ${PARSED_ARGS_NAME}")
            target_compile_features(${PARSED_ARGS_NAME} INTERFACE cxx_std_20)
        endif()
    else()
        message("Library is of shared object type")
        add_library(${PARSED_ARGS_NAME} ${PARSED_ARGS_TYPE} ${PARSED_ARGS_SOURCES})
        if(PARSED_ARGS_INCLUDE_DIRS)
            foreach(dir in ${PARSED_ARGS_INCLUDE_DIRS})
                target_include_directories(${PARSED_ARGS_NAME} PRIVATE ${dir})
            endforeach()
        endif()
        if(PARSED_ARGS_CXX20)
            message("CXX standard set to c++20 for library target ${PARSED_ARGS_NAME}")
            SET_CXX_20(${PARSED_ARGS_NAME})
        endif()
    endif ()
endfunction(SetupLibrary)


function(SetupExecutable)
    cmake_parse_arguments(
            PARSED_ARGS # prefix of output variables
            "CXX20" # list of names of the boolean arguments (only defined ones will be true)
            "NAME" # list of names of mono-valued arguments
            "SOURCES;DEPENDENCIES;INCLUDE_DIRS" # list of names of multi-valued arguments (output variables are lists)
            ${ARGN} # arguments of the function to parse, here we take the all original ones
    )
    # note: if it remains unparsed arguments, here, they can be found in variable PARSED_ARGS_UNPARSED_ARGUMENTS
    if(NOT PARSED_ARGS_NAME)
        message(FATAL_ERROR "You must provide a name")
    endif(NOT PARSED_ARGS_NAME)
    if(NOT PARSED_ARGS_SOURCES)
        message(FATAL_ERROR "You must provide sources for an executable")
    endif(NOT PARSED_ARGS_SOURCES)

    add_executable(${PARSED_ARGS_NAME} ${PARSED_ARGS_SOURCES})
    if(PARSED_ARGS_INCLUDE_DIRS)
        foreach(dir in ${PARSED_ARGS_INCLUDE_DIRS})
            target_include_directories(${PARSED_ARGS_NAME} PRIVATE ${dir})
        endforeach()
    endif()
    target_link_libraries(${PARSED_ARGS_NAME} ${PARSED_ARGS_DEPENDENCIES})
    if(PARSED_ARGS_CXX20)
        message("CXX standard set to c++20 for executable target ${PARSED_ARGS_NAME}")
        SET_CXX_20(${PARSED_ARGS_NAME})
    endif()
endfunction(SetupExecutable)
