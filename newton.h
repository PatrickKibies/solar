#ifndef NEWTON_H
#define NEWTON_H
#include <armadillo>

double f_grav_force(double f_m1, double f_m2, double f_r); // Calculates gravitation force from masses and distance
double f_acceleration(double f_m, double f_f); //Calculates acceleration from mass and force

arma::vec vec_grav_force_3D(arma::vec vec_distance, double f_m1, double f_m2); //Calculate gravitational mass vector from distance vector and masses
arma::vec vec_grav_acceleration(arma::vec vec_distance, double f_mass_object, double f_mass_central);



#endif