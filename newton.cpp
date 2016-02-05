#include <armadillo>


double f_grav_force(double f_m1, double f_m2, double f_r){
  double f_gravcon = 6.67408e-11; //m³ / (kg s^2)
  return (f_gravcon * f_m1*f_m2/(f_r*f_r)); // Newton
 }

double f_acceleration(double f_m, double f_f){
  return f_f/f_m;
}

arma::vec vec_distance(arma::vec vec_1, arma::vec vec_2){
    return vec_1 - vec_2;
}