#include <iostream>
#include <armadillo>
#include "newton.h"
#include "vector_operations.h"

int main(int argc, char **argv) {
  double f_mEarth, f_mSun, f_r;
  f_mEarth = 5.972e24;
  f_mSun = 1.989e30;
  f_r = 149.6e9;
   
 double f_Force = f_grav_force(f_mSun,f_mEarth,f_r);
  std::cout << "May the force be " << f_Force << std::endl;  
  std::cout << "Sun's accelaration: " << f_acceleration(f_mSun,f_Force) << std::endl;  
  std::cout << "Earth's accelaration: " << f_acceleration(f_mEarth,f_Force) << std::endl;  
  
  arma::vec vect1, vect2; // Define vectors
  vect1.set_size(3); //set size and allocate memory
  vect2.set_size(3);
  vect1.zeros(); //initialize with 0
  vect2.zeros();
  
  //Set some values
  vect1(0) = 149.6e9;
  vect1(1) = 0;
  vect1(2) = 0;
  vect2(2) = 0;
  vect2(1) = 0;
  vect2(0) = 0;


  
  std::cout << "Vectorial calculation of Force:"<<std::endl;
  std::cout << vec_grav_force_3D(vec_distance(vect1,vect2),f_mEarth,f_mSun) << std::endl;
  
 
  
  return 0;
}



