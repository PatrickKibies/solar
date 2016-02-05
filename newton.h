#ifndef NEWTON_H
#define NEWTON_H
#include <armadillo>

double f_grav_force(double f_m1, double f_m2, double f_r); // Calculates gravitation force from masses and distance
double f_acceleration(double f_m, double f_f); //Calculates acceleration from mass and force
arma::vec vec_distance(arma::vec vec_1, arma::vec vec_2); //Returns the distance vector between two armadillo vectors








#endif