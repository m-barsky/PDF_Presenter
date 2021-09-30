if(NOT BUILD_SHARED)

include(FetchContent)
include(PrependPrefix)

FetchContent_Declare(
   poppler
   GIT_REPOSITORY https://github.com/freedesktop/poppler.git
   GIT_TAG poppler-21.09.0
   INSTALL_COMMAND ""
)

FetchContent_Populate(poppler)

# define options to pass to poppler
set(POPPLER_OPTIONS "")

# options to make poppler compile - disables (unneccessary?) external dependencies
list(APPEND POPPLER_OPTIONS 
    ENABLE_DCTDECODER=none
    ENABLE_BOOST=OFF
    ENABLE_LIBOPENJPEG=none
)

list(APPEND POPPLER_OPTIONS
    ENABLE_LIBCURL=OFF
    ENABLE_ZLIB=OFF
    ENABLE_ZLIB_UNCOMPRESS=OFF
    ENABLE_CMS=none
) 

# don't compile tests
list(APPEND POPPLER_OPTIONS
    BUILD_GTK_TESTS=OFF
    BUILD_QT5_TESTS=OFF
    BUILD_QT6_TESTS=OFF
    BUILD_CPP_TESTS=OFF
    BUILD_MANUAL_TESTS=OFF
)

# disable unneccessary items
list(APPEND POPPLER_OPTIONS
    ENABLE_UTILS=OFF
    RUN_GPERF_IF_PRESENT=OFF
)

# disable library targets we don't need
list(APPEND POPPLER_OPTIONS
    ENABLE_GLIB=OFF
    ENABLE_GOBJECT_INTROSPECTION=OFF
    ENABLE_GTK_DOC=OFF
    ENABLE_QT5=OFF
    ENABLE_QT6=OFF
)

# enable the target we need to create cpp bindings and create a static lib
list(APPEND POPPLER_OPTIONS
    ENABLE_CPP=ON
    BUILD_SHARED_LIBS=OFF
)

# always build poppler as release build, even if we are in a debug build
list(APPEND POPPLER_OPTIONS
    CMAKE_BUILD_TYPE=Release
)

if(USE_LLD)
    find_program(LLD_LINKER lld)

    if(LLD_LINKER AND NOT WIN32)
        list(APPEND POPPLER_OPTIONS
            "CMAKE_C_FLAGS=-fuse-ld=lld"
            "CMAKE_CXX_FLAGS=-fuse-ld=lld"
        )
    endif(LLD_LINKER AND NOT WIN32)
endif(USE_LLD)

# prepend -D to each option
Prepend_Prefix(POPPLER_OPTIONS "-D")

# generate bulid files for poppler
execute_process(COMMAND cmake ${poppler_SOURCE_DIR} -G${CMAKE_GENERATOR} ${POPPLER_OPTIONS} WORKING_DIRECTORY ${poppler_BINARY_DIR})

# build poppler
execute_process(COMMAND cmake --build ${poppler_BINARY_DIR} WORKING_DIRECTORY ${poppler_BINARY_DIR})

set(POPPLER_HEADERS "")

list(APPEND POPPLER_HEADERS
    poppler-destination.h
    poppler-document.h
    poppler-embedded-file.h
    poppler-font.h
    poppler-font-private.h
    poppler-global.h
    poppler-image.h
    poppler-page.h
    poppler-page-renderer.h
    poppler-page-transition.h
    poppler-rectangle.h
    poppler-toc.h
)

Prepend_Prefix(POPPLER_HEADERS ${poppler_SOURCE_DIR}/cpp/)
list(APPEND POPPLER_HEADERS
    ${poppler_BINARY_DIR}/cpp/poppler_cpp_export.h
    ${poppler_BINARY_DIR}/cpp/poppler-version.h
)

# copy headers to generated/include/poppler/cpp/...
file(COPY ${POPPLER_HEADERS} DESTINATION ${PROJECT_SOURCE_DIR}/generated/include/poppler/cpp/)
target_include_directories(app PUBLIC ${PROJECT_SOURCE_DIR}/generated/include)

add_library(libpoppler STATIC IMPORTED)
set_target_properties(libpoppler PROPERTIES IMPORTED_LOCATION ${poppler_BINARY_DIR}/libpoppler${CMAKE_STATIC_LIBRARY_SUFFIX})

add_library(libpoppler_cpp STATIC IMPORTED)
set_target_properties(libpoppler_cpp PROPERTIES IMPORTED_LOCATION ${poppler_BINARY_DIR}/cpp/libpoppler-cpp${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(app PUBLIC libpoppler_cpp libpoppler)

else(NOT BUILD_SHARED)

find_package(Poppler)
target_link_libraries(app PUBLIC poppler)

endif(NOT BUILD_SHARED)

