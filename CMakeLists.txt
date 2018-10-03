cmake_minimum_required(VERSION 3.6)
project(mnist_1lnn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" -Iutil)

set(SOURCE_FILES main.c 1lnn.c 1lnn.h util/mnist-stats.c util/mnist-stats.h util/mnist-utils.c util/mnist-utils.h util/screen.c util/screen.h)
add_executable(mnist_1lnn ${SOURCE_FILES})