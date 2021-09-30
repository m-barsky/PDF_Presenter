include(FetchContent)
include(PrependPrefix)

if(NOT WIN32 AND NOT BUILD_SHARED)

FetchContent_Declare(
   freetype
   GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
   GIT_TAG VER-2-11-0
   INSTALL_COMMAND ""
)

FetchContent_Populate(freetype)

set(FREETYPE_OPTIONS "")

list(APPEND FREETYPE_OPTIONS
    BUILD_SHARED_LIBS=FALSE
    SKIP_INSTALL_ALL=TRUE
)

if(USE_LLD)
    find_program(LLD_LINKER lld)

    if(LLD_LINKER AND NOT WIN32)
        list(APPEND FREETYPE_OPTIONS
            "CMAKE_C_FLAGS=-fuse-ld=lld"
        )
    endif(LLD_LINKER AND NOT WIN32)
endif(USE_LLD)

# prepend -D to each option
Prepend_Prefix(FREETYPE_OPTIONS "-D")

# generate bulid files for freetype
execute_process(COMMAND cmake ${freetype_SOURCE_DIR} -G${CMAKE_GENERATOR} ${FREETYPE_OPTIONS} WORKING_DIRECTORY ${freetype_BINARY_DIR})

# build freetype
execute_process(COMMAND cmake --build ${freetype_BINARY_DIR} WORKING_DIRECTORY ${freetype_BINARY_DIR})

add_library(libfreetype STATIC IMPORTED)
set_target_properties(libfreetype PROPERTIES IMPORTED_LOCATION ${freetype_BINARY_DIR}/libfreetype${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(app PUBLIC libfreetype)

endif(NOT WIN32 AND NOT BUILD_SHARED)

