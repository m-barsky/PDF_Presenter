cmake_minimum_required(VERSION 3.12)

project(pdf_presenter)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

add_subdirectory(src)

option(USE_LLD ON)

if(USE_LLD)
    find_program(LLD_LINKER lld)

    if(LLD_LINKER AND NOT WIN32)
        string(APPEND CMAKE_C_FLAGS "-fuse-ld=lld")
        string(APPEND CMAKE_CXX_FLAGS "-fuse-ld=lld")
    endif(LLD_LINKER AND NOT WIN32)
endif(USE_LLD)

