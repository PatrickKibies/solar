cmake_minimum_required(VERSION 2.6)
project(solar)

add_executable(solar main.cpp)

install(TARGETS solar RUNTIME DESTINATION bin)
