add_executable(app main.cpp)
target_link_libraries(app PRIVATE poppler)

get_property(dirs1 TARGET app PROPERTY INCLUDE_DIRECTORIES)
get_property(dirs2 TARGET app PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
foreach(dir ${dirs2})
  message(STATUS "Interface include directory for my_target: ${dir}")
endforeach()

