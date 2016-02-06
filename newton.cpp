#include <armadillo>

double f_grav_force(double f_m1, double f_m2, double f_r){
  double f_gravcon = 6.67408e-11; //m³ / (kg s^2)
  return (f_gravcon * f_m1*f_m2/(f_r*f_r)); // Newton
 }

double f_acceleration(double f_m, double f_f){
  return f_f/f_m;
}

arma::vec vec_grav_force_3D(arma::vec vec_distance, double f_m1, double f_m2){  /// calculates a 3D gravitational force vector from a distance vector and two masses. 
  double f_distance;
  arma::vec vec_force, vec_unitvector;
  vec_force.set_size(vec_distance.n_elem);
  vec_unitvector.set_size(vec_distance.n_elem);
  vec_force.zeros();
  vec_unitvector.zeros();
    
  f_distance = norm(vec_distance,2); 
    
  vec_unitvector = normalise(vec_distance,2); //Normalised vector 
  vec_force = vec_unitvector * f_grav_force(f_m1, f_m2, f_distance);
   
  return vec_force;
 }