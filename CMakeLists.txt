cmake_minimum_required(VERSION 3.10)

# Project name and version
project(scicomp VERSION 1.0)

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Find Python
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
set(PYTHON_INCLUDE)
set(PYTHON_VERSION)
if(NOT PYTHON_INCLUDE)
  message(FATAL_ERROR "The path for the Python include folder is not set!")
endif()
if(NOT PYTHON_VERSION)
  message(FATAL_ERROR "The version of Python is not set!")
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC WITHOUT_NUMPY)
include_directories(${PYTHON_INCLUDE})
target_link_libraries(${PROJECT_NAME} ${PYTHON_VERSION})