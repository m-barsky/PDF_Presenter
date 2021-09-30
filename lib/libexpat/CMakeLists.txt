include(FetchContent)
include(PrependPrefix)

if(NOT WIN32 AND NOT BUILD_SHARED)

FetchContent_Declare(
   expat
   GIT_REPOSITORY https://github.com/libexpat/libexpat.git
   GIT_TAG R_2_4_1
   INSTALL_COMMAND ""
)

FetchContent_Populate(expat)

set(EXPAT_OPTIONS "")

# only build static libs
list(APPEND EXPAT_OPTIONS
    BUILD_SHARED_LIBS=FALSE
)

# dont install anything
list(APPEND EXPAT_OPTIONS
    EXPAT_ENABLE_INSTALL=FALSE
)

# dont build target we don't need
list(APPEND EXPAT_OPTIONS
    EXPAT_BUILD_TOOLS=FALSE
    EXPAT_BUILD_TESTS=FALSE
    EXPAT_BUILD_DOCS=FALSE
    EXPAT_BUILD_FUZZERS=FALSE
    EXPAT_BUILD_PKGCONFIG=FALSE
    EXPAT_OSSFUZZ_BUILD=FALSE
)

if(USE_LLD)
    find_program(LLD_LINKER lld)

    if(LLD_LINKER AND NOT WIN32)
        list(APPEND EXPAT_OPTIONS
            "CMAKE_C_FLAGS=-fuse-ld=lld"
            "CMAKE_CXX_FLAGS=-fuse-ld=lld"
        )
    endif(LLD_LINKER AND NOT WIN32)
endif(USE_LLD)

# prepend -D to each option
Prepend_Prefix(EXPAT_OPTIONS "-D")

# generate bulid files for expat
execute_process(COMMAND cmake ${expat_SOURCE_DIR}/expat -G${CMAKE_GENERATOR} ${EXPAT_OPTIONS} WORKING_DIRECTORY ${expat_BINARY_DIR})

# build expat
execute_process(COMMAND cmake --build ${expat_BINARY_DIR} WORKING_DIRECTORY ${expat_BINARY_DIR})

add_library(libexpat STATIC IMPORTED)
set_target_properties(libexpat PROPERTIES IMPORTED_LOCATION ${expat_BINARY_DIR}/libexpat${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(app PUBLIC libexpat)

endif(NOT WIN32 AND NOT BUILD_SHARED)

