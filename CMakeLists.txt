cmake_minimum_required(VERSION 2.8.3)

project(precaster_rps800)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(serial REQUIRED)

macro(targets)
	if(NOT "${target_suffix} " STREQUAL " ")
		get_rclcpp_information("${rmw_implementation}" "rclcpp${target_suffix}")
	endif()

	add_executable(precaster_rps800${target_suffix}
		src/main.cpp
		src/RPS800.cpp
	)
	ament_target_dependencies(precaster_rps800${target_suffix}
	  "rclcpp${target_suffix}"
	  "sensor_msgs"
	  "serial"
	)

	add_executable(precaster_rps800_listener${target_suffix}
		src/rps800_listener.cpp
	)
	ament_target_dependencies(precaster_rps800_listener${target_suffix}
	  "rclcpp${target_suffix}"
	  "sensor_msgs"
	)

	install(TARGETS
			precaster_rps800${target_suffix}
			precaster_rps800_listener${target_suffix}
		  	DESTINATION bin)
endmacro()

call_for_each_rmw_implementation(targets GENERATE_DEFAULT)

ament_package()
