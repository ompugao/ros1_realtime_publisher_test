project(testpublish)
find_package(realtime_tools REQUIRED)
find_package(roscpp REQUIRED)
find_package(std_msgs REQUIRED)
include_directories(${roscpp_INCLUDE_DIRS} ${std_msgs_INCLUDE_DIRS} ${realtime_tools_INCLUDE_DIRS})
link_directories(${roscpp_LIBRARY_DIRS} ${std_msgs_LIBRARY_DIRS} ${realtime_tools_LIBRARY_DIRS})

add_executable(publishtest publishtest.cpp)
target_link_libraries(publishtest ${roscpp_LIBRARIES} ${std_msgs_LIBRARIES} ${realtime_tools_LIBRARIES})
