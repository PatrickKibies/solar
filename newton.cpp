#include <armadillo>
 /** Sets a preprocessor directive for the gravitational constants in m^3 / kg s^2 in order to safe just 8 bytes of RAM... */
#define GRAVCON 6.67408e-11
#define DEBUG 0

/** Calculates a scalar garvitational force from two masses and their scalar distance*/
double f_grav_force(double f_mass1, double f_mass2, double f_distance){
  return (GRAVCON * f_mass1*f_mass2/(f_distance*f_distance));
 }

 
 /** Calculates the acceleration from a given mass and a given force.*/
double f_acceleration(double f_mass, double f_force){
  return f_force/f_mass;
}

/**Calculates a 3D gravitational force vector from a distance vector and two masses. Uses armadillo functions and datatypes. */
arma::vec vec_grav_force_3D(arma::vec vec_distance, double f_mass1, double f_mass2){  
  
  double f_distance;
  arma::vec vec_unitvector;
  vec_unitvector.set_size(vec_distance.n_elem);
  vec_unitvector.zeros();
    
  f_distance = norm(vec_distance,2); 
    
  vec_unitvector = normalise(vec_distance,2); //Normalised vector 
  return vec_unitvector * f_grav_force(f_mass1, f_mass2, f_distance);
}


arma::vec vec_grav_acceleration(arma::vec vec_distance, double f_mass_object, double f_mass_central){

	double distance = norm(vec_distance,2);
	arma::vec vec_unitvector;
	vec_unitvector.copy_size(vec_distance);
	vec_unitvector=  normalise(vec_distance,2);
	double force, acceleration; 
	force = f_grav_force(f_mass_object, f_mass_central, distance);
	acceleration=f_acceleration(f_mass_object,force);
	
	
	
	if (DEBUG){
	  std::cout << "newton.cpp -> vec_grav_acceleration DEBUG BEGIN" << std::endl;
	  std::cout << "vec_distance" << vec_distance << std::endl << std::endl;
	  std::cout << "distance" << distance << std::endl << std::endl;
	  std::cout << "f_mass_object --- f_mass_central" << f_mass_object << " --- " << f_mass_central;
	  std::cout << "vec_unitvector" << vec_unitvector << std::endl << std::endl;
	  std::cout << "force" << force <<std::endl;
	  std::cout << "acceleration" << acceleration <<std::endl;
	  std::cout << "newton.cpp -> vec_grav_acceleration DEBUG END return" << std::endl;
	}
	return -(vec_unitvector * acceleration);  
	
  
  }

