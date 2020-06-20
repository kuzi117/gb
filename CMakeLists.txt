cmake_minimum_required(VERSION 3.0)
project(gb)

# Set C++ standard.
set(CMAKE_CXX_STANDARD 17)

# Add project include directory.
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Build.
add_subdirectory(src)

