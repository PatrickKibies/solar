#include <iostream>
#include "newton.h"
#include <armadillo>


int main(int argc, char **argv) {
  double f_mEarth, f_mSun, f_r;
  f_mEarth = 5.972e24;
  f_mSun = 1.989e30;
  f_r = 149.6e9;
   
 double f_Force = f_grav_force(f_mSun,f_mEarth,f_r);
  std::cout << "May the force be " << f_Force << std::endl;  
  std::cout << "Sun's accelaration: " << f_acceleration(f_mSun,f_Force) << std::endl;  
  std::cout << "Earth's accelaration: " << f_acceleration(f_mEarth,f_Force) << std::endl;  
  
  arma::vec vect1, vect2;
  vect1.set_size(3);
  vect2.set_size(3);
  vect1.zeros();
  vect2.zeros();
  
  std::cout << arma::accu(vect1) << std::endl;
  
  vect1(0) = 1;
  vect1(1) = 2;
  vect1(2) = 3;
  vect2(2) = 1;
  vect2(1) = 2;
  vect2(0) = 4;

  std::cout << accu(vec_distance(vect1,vect2)) << std::endl;
  
  
  std::cout << arma::accu(vect1) << std::endl;
  
  
  
  
  
  return 0;
}



