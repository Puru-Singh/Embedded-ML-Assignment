cmake_minimum_required(VERSION 3.5)
project(OpenCVExample)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories from OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Create an executable
add_executable(OpenCVExample src/main.cpp)

# Link OpenCV libraries 
target_link_libraries(OpenCVExample ${OpenCV_LIBS})
