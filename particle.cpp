
// #include "particle.h"
#include <vector>
#include <armadillo>
#include <cstdlib>
#include <math.h>
#include "particle.h"
#include "newton.h"
#include "vector_operations.h"
#include "dynamics.h"
#include "physics.h"
  
  
  /**
   * \class particle
   * \brief Class which holds all informations and methods to create and manage massive particles
   */
  

  
  /**
   * \brief Creator method for a particle*
   * \param number An integer number to index the particle created
   * 
   * Initial positioning is somewhat arbitrary - maybe we should improve that
   */
  
void particle::createAParticle(int number){

  s_type = "N";
  
  vec_location0.set_size(3);
  vec_location1.set_size(3);
  vec_location2.set_size(3);
  vec_location0.zeros();
  vec_location1.zeros();
  vec_location2.zeros();
  
  vec_speed0.set_size(3);
  vec_speed1.set_size(3);
  vec_speed2.set_size(3);
  
  vec_mainForce.set_size(3);
  vec_mainForce.zeros();
  vec_dist.set_size(3);
  vec_dist.zeros();
  vec_internForce.set_size(3);
  vec_internForce.zeros();
  
  d_intern_Epot=0;
  
  l_min=1e10;
  l_max=2e10;
  
  f_radius=200000; // @ KowalskiTheP What does that mean?
  
 // double mass_LO=1.0;
 // double mass_HI=9.9;
  //std::srand(42);
  /*f_massPower =20 + (std::rand() % (int)(25 - 20 + 1));
  f_massFactor= mass_LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(mass_HI-mass_LO)));
  d_mass=f_massFactor*pow(10,f_massPower);*/
  
  d_mass =5972000;
  i_number=number;
  d_Epot=0;

  // ifloat LO=-9.0;
  // float HI=9.0;
  
  /*
  vec_location1(0) = std::sin(0.2*number*3.1415) * 149.5978707 + (number*2e2); //2e10
  vec_location1(1) = std::cos(0.2*number*3.1415) * 149.5978707 - (number*2e2);
  */
  vec_location1(0) = number * 149.5978707;
  
  //std::cout << norm(vec_location1) <<" "<< number << std::endl;
  double gravcon =  66740800000;
  vec_location0 = vec_location1;
  vec_location0(1) = vec_location1(1) - (std::sqrt(2* gravcon *1989000000000*(1/(number*149.5978707)-1/(2*number*149.5978707))) * 0.00000000008640); //29780000000;
  
  
}
  

  /**
   * \brief Method for gathering all forces on this particle - disfunctional now.
   */
void particle::getAllForces(std::vector<particle>arrayOfAllParticles, int i_tnp){
#pragma omp parallel for   
      for(int i=i_number+1;i<i_tnp;i=i+1){  
	vec_dist = vec_distanceVec(vec_location1,arrayOfAllParticles[i].vec_location1);
	vec_internForce = vec_grav_force_3D(vec_dist, d_mass, arrayOfAllParticles[i].d_mass);
	//d_intern_Epot = d_calc_Epot(vec_dist, d_mass, arrayOfAllParticles[i].d_mass); 
	vec_mainForce = vec_mainForce + vec_internForce;
	//d_Epot = d_Epot + d_intern_Epot;
	arrayOfAllParticles[i].vec_mainForce = arrayOfAllParticles[i].vec_mainForce - vec_internForce;
	//arrayOfAllParticles[i].d_Epot = arrayOfAllParticles[i].d_Epot + d_intern_Epot;
	//vec_internForce.zeros();
	//d_intern_Epot=0;
      }
      vec_mainAcceleration=(vec_mainForce/d_mass);
}
  

/**
 * \brief Performs an Simulation step by calling the integrator
 * */
void particle::propagate(double d_timeStep){
  vec_location2 = vec_verlet_step(vec_location0, vec_location1, vec_mainAcceleration, d_timeStep);
  vec_location0 = vec_location1;
  vec_location1 = vec_location2;
}

/**
 * \brief Sets the current loication of the particle
 * */
void particle::setCurrentLocation(arma::vec vec_inLocation){
  vec_location1=vec_inLocation;
}

/** 
 * \brief Sets the previous position of the particle (which is used by verlet like integrators and to calculate velocities)
 * */
 void particle::setOldLocation(arma::vec vec_inLocation){
   vec_location0 = vec_inLocation;
   }

   /**
    * \brief Sets the current forces*
    */
void particle::setForce(arma::vec vec_inForce){
   vec_mainForce = vec_inForce;
}

/**
 \brief Adds an force vector to the current force. Useful for gathering total forces on a particle 
 */

void particle::addToForce(arma::vec vec_inForce){
      vec_mainForce = vec_inForce + vec_mainForce;
}

/**
 \brief Sets the value of potential energy (what for?)
 */
void particle::setEpot(double d_inEpot){
   d_Epot = d_inEpot;
}

/**
 \brief Adds to the value of potential energy
 
 */
void particle::addToEpot(double d_inEpot){
   d_Epot = d_Epot + d_inEpot;
}


/**
 \brief Calculates the accelaration from mean Force to the particle and its mass
 */

void particle::calculateAcceleration()
{
vec_mainAcceleration = vec_mainForce/d_mass;
}


/**
 *\brief returns the current location 
  \return Armadillo vector holding the current location*/
arma::vec particle::getCurrentLocation(){
    return vec_location1;
}
/**
 \brief returns the previous location
 \return Armadillo vector holding the old location
 */
arma::vec particle::getOldLocation(){
    return vec_location0;
}

