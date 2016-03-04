cmake_minimum_required(VERSION 2.6)
project(solar)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g3 -Og -fopenmp -pedantic -fopt-info -ftree-vectorize -ftree-vectorizer-verbose=2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2 -fopenmp -ftree-vectorize -fopt-info -ftree-vectorizer-verbose=2")

find_package(Armadillo)
find_package(Boost)

add_library(newton newton.h newton.cpp)
add_library(vectorOps vector_operations.h vector_operations.cpp)
add_library(particle particle.h particle.cpp)
add_library(dynamics dynamics.h dynamics.cpp)
add_library(solar_io solar_io.h solar_io.cpp)
add_executable(solar main.cpp)


target_link_libraries(solar_io ${Boost_LIBRARIES})
target_link_libraries(particle newton armadillo dynamics)
target_link_libraries(newton vectorOps armadillo)
target_link_libraries(solar newton dynamics armadillo particle solar_io boost_system ${Boost_LIBRARIES} ${Boost_TIMER_LIBRARY})




if(build_doc)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()


install(TARGETS solar RUNTIME DESTINATION bin)
