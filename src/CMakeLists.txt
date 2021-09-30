cmake_policy(SET CMP0076 NEW)

add_executable(app)

target_include_directories(app PRIVATE views models controllers utils)

add_subdirectory(models)
add_subdirectory(views)
add_subdirectory(controllers)
add_subdirectory(utils)

target_sources(app PRIVATE
    App.cpp
    App.h
)

target_compile_options(app PUBLIC "-Wall" "-Wpedantic" "-Wextra")
target_compile_options(app PUBLIC "$<$<CONFIG:DEBUG>:-O0;-g3;-fsanitize=leak>")
target_link_options(app PUBLIC "$<$<CONFIG:DEBUG>:-fsanitize=leak>")

set_target_properties(app PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

# find_package(Poppler REQUIRED)
# target_link_libraries(app PUBLIC poppler)

find_package(wxWidgets COMPONENTS core base adv richtext REQUIRED)
include(${wxWidgets_USE_FILE})
set(wxWidgets_USE_STATIC ON)
target_link_libraries(app PUBLIC ${wxWidgets_LIBRARIES})

