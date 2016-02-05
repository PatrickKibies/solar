cmake_minimum_required(VERSION 2.6)
project(solar)

find_package(Armadillo)
find_package(LAPACK)
find_package(BLAS)


add_library(newton newton.h newton.cpp vector_operations.h vector_operations.cpp)

add_executable(solar main.cpp)

target_link_libraries(solar newton blas lapack armadillo)
target_link_libraries(newton  blas lapack armadillo)

install(TARGETS solar RUNTIME DESTINATION bin)
