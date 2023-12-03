# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(Sequential)

#Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set the OpenCV_DIR variable
set(OpenCV_DIR "C:/opencv/sources/cmake")

# Find the OpenCV package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Sequential Secuencial/Secuencial.cpp)

# Link the executable target against the OpenCV libraries
target_link_libraries(Sequential ${OpenCV_LIBS})
