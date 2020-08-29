cmake_minimum_required(VERSION 3.0)
project(thread_samples)

#Set default build type
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#Set C++ standard 
set(CMAKE_CXX_STANDARD 14)

#Define output dir 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

#Enable thread support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread")

#Set include directories 
include_directories("${CMAKE_SOURCE_DIR}/include")

#Set source files to be compiled 
set(PROJECT_SRC_FILES "./src/thread_barrier.cpp")

#Add executable 
add_executable(main main.cpp "${PROJECT_SRC_FILES}")
