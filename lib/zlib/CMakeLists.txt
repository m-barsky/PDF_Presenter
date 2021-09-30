if(NOT BUILD_SHARED)

include(FetchContent)
include(PrependPrefix)

FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG v1.2.11
    INSTALL_COMMAND ""
)

FetchContent_Populate(zlib)

set(ZLIB_OPTIONS "")

# dont install any files
list(APPEND ZLIB_OPTIONS
    SKIP_INSTALL_ALL=TRUE
)


add_library(libzlib STATIC IMPORTED)
set_target_properties(libzlib PROPERTIES IMPORTED_LOCATION ${zlib_BINARY_DIR}/libz${CMAKE_STATIC_LIBRARY_SUFFIX})




if(USE_LLD)
    find_program(LLD_LINKER lld)

    if(LLD_LINKER AND NOT WIN32)
        list(APPEND ZLIB_OPTIONS
            "CMAKE_C_FLAGS=-fuse-ld=lld"
        )
    endif(LLD_LINKER AND NOT WIN32)
endif(USE_LLD)

# prepend -D to each option
Prepend_Prefix(ZLIB_OPTIONS "-D")

# generate build files for zlib
execute_process(COMMAND cmake ${zlib_SOURCE_DIR} -G${CMAKE_GENERATOR} ${ZLIB_OPTIONS} WORKING_DIRECTORY ${zlib_BINARY_DIR})

# build zlib
execute_process(COMMAND cmake --build ${zlib_BINARY_DIR} WORKING_DIRECTORY ${zlib_BINARY_DIR})


target_link_libraries(app PUBLIC libzlib)

endif(NOT BUILD_SHARED)

