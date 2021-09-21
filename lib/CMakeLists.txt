find_package(Poppler REQUIRED)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})
target_link_libraries(app ${wxWidgets_LIBRARIES})

