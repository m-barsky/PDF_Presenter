include(FetchContent)

FetchContent_Declare(
    poppler
    GIT_REPOSITORY https://github.com/freedesktop/poppler.git
    GIT_TAG poppler-21.09.0
)

option(BUILD_GTK_TESTS "" OFF)
option(BUILD_QT5_TESTS "" OFF)
option(BUILD_QT6_TESTS "" OFF)
option(BUILD_CPP_TESTS "" OFF)
option(BUILD_MANUAL_TESTS "" OFF)
option(ENABLE_BOOST "" OFF)
option(ENABLE_UTILS "" OFF)
option(ENABLE_CPP "" ON)
option(ENABLE_GLIB "" OFF)
option(ENABLE_GOBJECT_INTROSPECTION "" OFF)
option(ENABLE_GTK_DOC "" OFF)
option(ENABLE_QT5 "" OFF)
option(ENABLE_QT6 "" OFF)
option(BUILD_SHARED_LIBS "" OFF)
option(RUN_GPERF_IF_PRESENT "" OFF)

set(ENABLE_DCTDECODER "none" CACHE STRING "")
set(ENABLE_LIBOPENJPEG "none" CACHE STRING "")

# set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR} CACHE PATH "Where external libraries should place their headers" FORCE)

FetchContent_Populate(poppler)
execute_process(COMMAND patch ${poppler_SOURCE_DIR}/CMakeLists.txt ${CMAKE_CURRENT_SOURCE_DIR}/Poppler_CMakeLists.patch)
execute_process(COMMAND patch ${poppler_SOURCE_DIR}/cpp/CMakeLists.txt ${CMAKE_CURRENT_SOURCE_DIR}/Poppler_cpp_CMakeLists.patch)
execute_process(COMMAND patch ${poppler_SOURCE_DIR}/cpp/tests/CMakeLists.txt ${CMAKE_CURRENT_SOURCE_DIR}/Poppler_cpp_tests_CMakeLists.patch)

# execute_process(COMMAND patch ${CMAKE_CURRENT_SOURCE_DIR}/Poppler_CMakeLists.patch ${poppler_SOURCE_DIR}/CMakeLists.txt)
message("patching ${CMAKE_CURRENT_SOURCE_DIR}/Poppler_CMakeLists.patch to ${poppler_SOURCE_DIR}/CMakeLists.txt")
# execute_process(COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/patch_poppler.py ${poppler_SOURCE_DIR}/CMakeLists.txt)
# execute_process(COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/extract_poppler_includes.py ${poppler_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${poppler_SOURCE_DIR} ${poppler_BINARY_DIR})

# target_include_directories(poppler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

