cmake_minimum_required(VERSION 2.6)
project(solar)

find_package(Armadillo)

add_library(newton newton.h newton.cpp)
add_executable(solar main.cpp newton.cpp )

install(TARGETS solar RUNTIME DESTINATION bin)
