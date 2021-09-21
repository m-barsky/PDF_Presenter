cmake_minimum_required(VERSION 3.12)

project(pdf_presenter)

# set(CMAKE_CXX_STANDARD 17)
# add_compile_options("-Wall" "-Wpedantic" "-Wextra")

# add_compile_options("$<$<CONFIG:DEBUG>:-O0;-g3;-fsanitize=leak>")
# add_link_options("$<$<CONFIG:DEBUG>:-fsanitize=leak>")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

add_subdirectory(src)

