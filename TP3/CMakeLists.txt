cmake_minimum_required(VERSION 3.3)
project(TP3)
include_directories(at)

find_package( OpenCV REQUIRED )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

set(SOURCE_FILES main.cpp Eigenfaces.cpp at.txt)
configure_file(at.txt at.txt COPYONLY)
file(COPY at DESTINATION .)
add_executable(TP3 ${SOURCE_FILES})
target_link_libraries( TP3 ${OpenCV_LIBS} )