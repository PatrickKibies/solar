cmake_minimum_required(VERSION 2.6)
project(solar)

find_package(Armadillo)
find_package(LAPACK)
find_package(BLAS)

add_library(newton newton.h newton.cpp)
add_library(vectorOps vector_operations.h vector_operations.cpp)
add_library(particle particle.h particle.cpp)
add_executable(solar main.cpp)

target_link_libraries(vectorOps armadillo)
target_link_libraries(solar newton armadillo particle)
target_link_libraries(newton vectorOps armadillo)
target_link_libraries(particle newton armadillo)

install(TARGETS solar RUNTIME DESTINATION bin)
