cmake_minimum_required(VERSION 2.8.3)
project(precaster_rangefinder_rps800)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs std_msgs serial)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(rps800 src/main.cpp src/RPS800.cpp)
target_link_libraries(rps800 ${catkin_LIBRARIES})
add_dependencies(rps800 precaster_rangefinder_rps800)

add_executable(rps800_listener src/rps800_listener.cpp)
target_link_libraries(rps800_listener ${catkin_LIBRARIES})
add_dependencies(rps800_listener precaster_rangefinder_rps800)


install(
	TARGETS rps800 rps800_listener
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
PATTERN ".git" EXCLUDE)
