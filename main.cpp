#define _USE_MATH_DEFINES
#include <iostream>
#include <armadillo>
#include <math.h>
#include "newton.h"
#include "vector_operations.h"
#include "dynamics.h"

int main(int argc, char **argv) {
  
  double f_mEarth, f_mSun, f_r; 
  f_mEarth = 5.972e24; 
  f_mSun = 1.989e30; 
  f_r = 149.6e9; 
   
 double f_Force = f_grav_force(f_mSun,f_mEarth,f_r);
  //std::cout << "May the force be " << f_Force << std::endl;  
  //std::cout << "Sun's accelaration: " << f_acceleration(f_mSun,f_Force) << std::endl;  
 // std::cout << "Earth's accelaration: " << f_acceleration(f_mEarth,f_Force) << std::endl;  
  
  arma::vec vect1, vect2; // Define vectors
  vect1.set_size(3); //set size and allocate memory
  vect2.set_size(3);
  vect1.zeros(); //initialize with 0
  vect2.zeros();
 
  float f_angle = (0./360.) * (2. * M_PI);
  
  //Set some values
  vect1(0) = 149.6e9 * std::cos(f_angle);
  vect1(1) = 149.6e9 * std::sin(f_angle);
  vect1(2) = 0;
  vect2(2) = 0;
  vect2(1) = 0;
  vect2(0) = 0;
  
 // std::cout << "Vectorial calculation of Force:"<<std::endl;
 // std::cout << vec_grav_force_3D(vec_distanceVec(vect1,vect2),f_mEarth,f_mSun) << std::endl;
 // std::cout << "Force vector norm: " << std::endl;
 // std::cout << norm(vec_grav_force_3D(vec_distanceVec(vect1,vect2),f_mEarth,f_mSun)) << std::endl;  
  
  
  arma::vec vec_initial_velocity, vec_Earth_current_Position, vec_Earth_old_Position, vec_temp, vec_accel;
  
  vec_initial_velocity.set_size(3);
  vec_initial_velocity.zeros();
  vec_initial_velocity(1) = 30e3; //ca. max speed of earth in perihel
  vec_initial_velocity(2) = 0.0000;
 
  
  vec_Earth_old_Position.set_size(3);
  vec_Earth_old_Position.zeros();
  vec_Earth_old_Position(0) = 0; //Distance Sun earth, metres
  vec_Earth_old_Position(1) = 0;
  vec_Earth_old_Position(2) = f_r;
  
  

  
  vec_Earth_current_Position.set_size(3);
  vec_Earth_current_Position.zeros();
  vec_Earth_current_Position = vec_positionVelocity(vec_Earth_old_Position, vec_initial_velocity, 300);
  
  vec_temp.set_size(3);
  
  for(int i = 1; i<=1e6; i++){
    
    
    vec_temp = vec_Earth_old_Position;
    vec_Earth_old_Position = vec_Earth_current_Position;
    vec_accel = vec_grav_acceleration(vec_Earth_current_Position, f_mEarth, f_mSun);
    vec_Earth_current_Position = vec_verlet_step(vec_temp, vec_Earth_current_Position, vec_accel, 300);

    
  // std::cout << i << "Position:" << std::endl << vec_Earth_old_Position << std::endl  <<vec_Earth_current_Position << "vec_accel" << std::endl << vec_accel << std::endl << std::endl << norm(vec_Earth_current_Position) <<std::endl;
    
   std::cout << vec_Earth_current_Position(0) <<"	"<< vec_Earth_current_Position(1) <<"	"<<vec_Earth_current_Position(2) << std::endl;
    
  }
  
  
  
  
  
  
  
  
  
  
  
  
   
  return 0;
}
