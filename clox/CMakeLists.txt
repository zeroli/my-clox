# CMakeList.txt : CMake project for clox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(clox)

# Add source to this project's executable.
aux_source_directory(. SRCS)
add_executable (clox ${SRCS})

# TODO: Add tests and install targets if needed.
