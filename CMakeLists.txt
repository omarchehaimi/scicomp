cmake_minimum_required(VERSION 3.10)

# Project name and version
project(scicomp VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)

# Download Matplot++ library
include(FetchContent)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master)
FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp src/utils/cli.cpp 
                               src/utils/plotting.cpp src/lv/lv.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC matplot)