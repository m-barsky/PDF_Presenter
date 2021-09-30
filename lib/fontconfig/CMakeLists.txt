if(NOT WIN32)
message(STATUS "non windows OS, using fontconfig")

if(BUILD_SHARED)
message(STATUS "linking against systems fontconfig")

# find and install fontconfig
include(FindFontconfig)

find_package(Fontconfig REQUIRED)
target_link_libraries(app PUBLIC ${Fontconfig_LIBRARIES})

# fontconfig requires freetype so we link to the .so
include(FindFreetype)

find_package(Freetype REQUIRED)
target_link_libraries(app PUBLIC ${FREETYPE_LIBRARIES})

else(BUILD_SHARED)
message(STATUS "linking against fontconfig statically")

set(FONTCONFIG_ARCHIVE "fontconfig-2.13.94.tar.xz")
set(fontconfig_SOURCE_DIR ${PROJECT_BINARY_DIR}/_deps/fontconfig-src)
set(fontconfig_BINARY_DIR ${PROJECT_BINARY_DIR}/_deps/fontconfig-build)

message(STATUS "downloading fontconfig")
# download fontconfig
execute_process(COMMAND wget https://www.freedesktop.org/software/fontconfig/release/fontconfig-2.13.94.tar.xz)

message(STATUS "unpacking fontconfig")
# move unpack to source dir and delete tar
file(MAKE_DIRECTORY ${fontconfig_SOURCE_DIR})
execute_process(COMMAND tar -xvf fontconfig-2.13.94.tar.xz -C ${fontconfig_SOURCE_DIR} --strip-components=1)
file(REMOVE ${FONTCONFIG_ARCHIVE})

# create binary dir (used for junk to install fontconfig stuff)
file(MAKE_DIRECTORY ${fontconfig_BINARY_DIR})

message(STATUS "building fontconfig")
# configure and build
execute_process(COMMAND ./configure --disable-shared --enable-static --sysconfdir=/etc --prefix=${fontconfig_BINARY_DIR} --exec-prefix=${fontconfig_BINARY_DIR} --mandir=${fontconfig_BINARY_DIR}  WORKING_DIRECTORY ${fontconfig_SOURCE_DIR})
execute_process(COMMAND make WORKING_DIRECTORY ${fontconfig_SOURCE_DIR})

add_library(libfontconfig STATIC IMPORTED)
set_target_properties(libfontconfig PROPERTIES IMPORTED_LOCATION ${fontconfig_SOURCE_DIR}/src/.libs/libfontconfig${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(app PUBLIC libfontconfig)

endif(BUILD_SHARED)

endif(NOT WIN32)

