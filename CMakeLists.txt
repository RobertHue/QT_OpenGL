cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

#-----------------------------------------------------------------------------
# Define the project name
set(PROJECT_NAME    "3D-Content_Creator")
set(EXECUTABLE_NAME "3D-Content_Creator")
set(TEST_NAME       "3D-Content_Creator_Tests")
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#-----------------------------------------------------------------------------
# generate a message
message(STATUS "~~~ ${PROJECT_NAME} v${PROJECT_VERSION} ~~~")
message(STATUS "Target: ${CMAKE_SYSTEM_PROCESSOR} (${CMAKE_SYSTEM_NAME})")
message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
message(STATUS "PROJECT_NAME : ${PROJECT_NAME}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")

#-----------------------------------------------------------------------------
# set cmake module path
# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#-----------------------------------------------------------------------------
# configure and find BOOST
set(Boost_USE_STATIC_LIBS        ON) 	# only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.69.0 REQUIRED COMPONENTS system filesystem unit_test_framework serialization)

#-----------------------------------------------------------------------------
# configure and find QT5
set(CMAKE_INCLUDE_CURRENT_DIR ON)	# Find includes in corresponding build directories
set(CMAKE_AUTOMOC ON)	# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOUIC OFF)	# Create code from a list of Qt designer ui files
find_package(Qt5 REQUIRED COMPONENTS Widgets OpenGL Core GUI)	# Find the QtWidgets library

#-----------------------------------------------------------------------------
# OpenGL & GLEW library
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
#find_package(glfw3 REQUIRED)

#-----------------------------------------------------------------------------
# look for dependencies
file(GLOB_RECURSE DEPENDENCIES "source/*.hpp" "source/*.cpp" "source/*.h" "source/*.c")
message(STATUS "DEPENDENCIES : ${DEPENDENCIES}")

#-----------------------------------------------------------------------------
# VS related
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

#-----------------------------------------------------------------------------
# Application
add_subdirectory("source")

#-----------------------------------------------------------------------------
# Testing
add_subdirectory("tests")
