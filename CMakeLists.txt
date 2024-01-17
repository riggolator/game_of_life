cmake_minimum_required(VERSION 3.26.3)
project(GoL)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}
	src/main.cc
	src/grid.cc)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)	

