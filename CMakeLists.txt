cmake_minimum_required(VERSION 3.11)
project(GP_VALVE_DIAGRAM CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(gp_valve_diagram
		
	src/matherials.h
	src/physics.h
	src/math.h

	src/console.cpp
	src/console.h

	src/settings.cpp
	src/settings.h

	src/valve.cpp
	src/valve.h

	src/main.cpp
 "src/handler.h" "src/handler.cpp")