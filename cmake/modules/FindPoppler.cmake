# inspired by https://github.com/freedesktop/poppler/blob/f70e352429e3b565262251b1150e77e8638bed6c/cmake/modules/FindCairo.cmake

if(POPPLER_INCLUDE_DIRS AND POPPLER_LIBRARIES)
    set(POPPLER_FOUND TRUE)
else(POPPLER_INCLUDE_DIRS AND POPPLER_LIBRARIES)
if(NOT WIN32)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(_pc_poppler poppler REQUIRED)
    find_package_handle_standard_args(poppler DEFAULT_MSG _pc_poppler_LIBRARIES _pc_poppler_CFLAGS)

    if(_pc_poppler_FOUND)
        set(POPPLER_FOUND TRUE)
    endif(_pc_poppler_FOUND)
else(NOT WIN32)
    # ???
    set(POPPLER_FOUND FALSE)
endif(NOT WIN32)

if(POPPLER_FOUND)
    set(POPPLER_FOUND FALSE)
    find_library(POPPLER_LIBRARY poppler HINTS ${_pc_poppler_STATIC_LIBRARY_DIRS})
    set(POPPLER_LIBRARIES ${POPPLER_LIBRARY})
    
    find_path(POPPLER_INCLUDE_DIR poppler/cpp/poppler-document.h HINTS ${_pc_poppler_INCLUDE_DIRS} PATH_SUFFIXES poppler)
    set(POPPLER_INCLUDE_DIRS ${POPPLER_INCLUDE_DIRS})
endif(POPPLER_FOUND)

endif(POPPLER_INCLUDE_DIRS AND POPPLER_LIBRARIES)

mark_as_advanced(POPPLER_CFLAGS POPPLER_INCLUDE_DIRS POPPLER_LIBRARIES)

