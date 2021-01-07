cmake_minimum_required(VERSION 2.8)

project(mat_lib_gen C CXX)

#message(STATUS "libraries:")
#
#message(STATUS "  'mat_lib' will be generated")
## mat_lib library
#add_library(
#  mat_lib
#  matrix.cpp
#)

find_package(Boost 1.71.0 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

message(STATUS "targets:")
# testing_mat_lib
message(STATUS "  'mat_lib_gen' will be generated")
add_executable(
        main
        main.cpp
)
target_link_libraries(main LINK_PUBLIC ${Boost_LIBRARIES})