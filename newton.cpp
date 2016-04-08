#include <armadillo>
 /** Sets a preprocessor directive for the gravitational constants in m^3 / kg s^2 in order to safe just 8 bytes of RAM... */
#define GRAVCON 66740800000
#define DEBUG 0

/**
 * @file newton.cpp
 * @brief Routines for classical mechanics

 This file contains a set of functions which are related to classical mechanics. You will find routines for calculating garvitational forces and acccelerations.
 */

/** 
 @brief  Calculates a scalar garvitational force from two masses and their scalar distance 
 */


/**
 * @brief Calculates a scalar gravitational force between two bodies
 * @param f_mass1 Mass of the first body
 * @param f_mass2 Mass of the second body
 * @param f_distance scalar distance between both bodies
 * @return Scalar force between both bodies
 * */

double f_grav_force(double f_mass1, double f_mass2, double f_distance){
  return (GRAVCON * f_mass1*f_mass2/(f_distance*f_distance));
 }

 
 /** @brief Calculates the acceleration from a given mass and a given force.
    @param f_mass mass of body
    @param f_force force applied to the body
    @return scalar acceleration of the body*/
double f_acceleration(double f_mass, double f_force){
  return f_force/f_mass;
}

/** @brief Calculates a 3D gravitational force vector from a distance vector and two masses. Uses armadillo functions and datatypes. 
    @param vec_distance armadillo vector holding the distance between the bodies
    @param f_mass1 mass of first body
    @param f_mass2 mass of second body
    @return armadillo vector between both bodies*/
arma::vec vec_grav_force_3D(arma::vec vec_distance, double f_mass1, double f_mass2){  
  
  double f_distance;
  arma::vec vec_unitvector;
  vec_unitvector.set_size(vec_distance.n_elem);
  vec_unitvector.zeros();
    
  f_distance = norm(vec_distance,2); 
    
  vec_unitvector = normalise(vec_distance,2); //Normalised vector 
  return vec_unitvector * f_grav_force(f_mass1, f_mass2, f_distance);
}

/**
@brief Calculates an acceleration vector from given masses and distance vecctor
@param vec_distance distance vector between the bodies
@param f_mass_object mass of accelerated vector
@param f_mass_central mass of fixed object
*/
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

