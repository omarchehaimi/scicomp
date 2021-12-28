cmake_minimum_required(VERSION 3.10)

# Project name and version
project(scicomp VERSION 1.0)

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp src/utils/cli.cpp)

# Add the libraries
# target_link_libraries(cotom PUBLIC) 

# Install in bin
# install(TARGETS cotom DESTINATION bin)
