if(NOT BUILD_SHARED)

include(FetchContent)
include(PrependPrefix)

FetchContent_Declare(
    libpng
    GIT_REPOSITORY https://github.com/glennrp/libpng.git
    GIT_TAG v1.6.37
)

FetchContent_GetProperties(libpng)

if(NOT ${libpng_POPULATED})
    FetchContent_Populate(libpng)

    option(PNG_SHARED "static linking only" OFF)
    option(PNG_STATIC "static linking only" ON)
    option(PNG_DEBUG "library is always on release build" OFF)
    option(PNG_FRAMEWORK "osx only option" OFF)
    option(PNG_HARDWARE_OPTIMIZATIONS "" ON)
    option(PNG_TESTS "using tested release build" OFF)
    option(SKIP_INSTALL_ALL "we only need the library" ON)


    add_subdirectory(${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})
endif(NOT ${libpng_POPULATED})

target_link_libraries(app PUBLIC libpng16.a)

endif(NOT BUILD_SHARED)

