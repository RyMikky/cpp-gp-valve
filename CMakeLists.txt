cmake_minimum_required(VERSION 3.11)
project(GP_VALVE_DIAGRAM CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

add_executable(gp_valve_diagram
		
	src/matherials.h
	src/physics.h
	src/math.h

	src/console.cpp
	src/console.h

	src/settings.cpp
	src/settings.h

	src/handler.cpp
	src/handler.h

	src/valve.cpp
	src/valve.h

	src/main.cpp

	3rd_party/matplotlibcpp.h
)

find_package(Python3 COMPONENTS Interpreter Development NumPy)
if (${Python3_FOUND})
	message("Python3 found")
  include_directories(${Python3_INCLUDE_DIRS})

	if (DEBUG_POSTFIX)
		message("using debug Python3 lib")
		target_link_libraries(gp_valve_diagram ${Python3_LIBRARY_DEBUG})
	else()
		message("using release Python3 lib")
		target_link_libraries(gp_valve_diagram ${Python3_LIBRARY_RELEASE})
	endif()
else()
  message(FATAL_ERROR "Python3 not found, please install it.")
endif()

find_package(NumPy)
if (${PYTHON_NUMPY_FOUND})
	message("NumPy found")
  include_directories(${PYTHON_NUMPY_INCLUDE_DIR})
  
else()
  message(WARNING "Python3 NumPy not found, proceeding with -DWITHOUT_NUMPY."
  " Some functions might not work.")
  add_definitions(-DWITHOUT_NUMPY)
endif()