
// #include "particle.h"
#include <vector>
#include <armadillo>
#include <cstdlib>
#include <math.h>
#include "particle.h"
#include "newton.h"
#include "vector_operations.h"
#include "dynamics.h"
  

  
void particle::createAParticle(int number){

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
  
  l_min=1e10;
  l_max=2e10;
  
  f_radius=200000; // @ KowalskiTheP What does that mean?
  
  double mass_LO=1.0;
  double mass_HI=9.9;
  //std::srand(42);
  /*f_massPower =20 + (std::rand() % (int)(25 - 20 + 1));
  f_massFactor= mass_LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(mass_HI-mass_LO)));
  d_mass=f_massFactor*pow(10,f_massPower);*/
  
  d_mass = 3e24;
  i_number=number;

  float LO=-9.0;
  float HI=9.0;
  
  vec_location1(0) = std::sin(0.2*number*3.1415) * 149e9 + (number*2e10);
  vec_location1(1) = std::cos(0.2*number*3.1415) * 149e9 - (number*2e10);
  
  
  std::cout << norm(vec_location1) <<" "<< number << std::endl;
  
  
  vec_location0 = vec_location1;
  vec_location0(2) = vec_location1(2) + number*3e4;
  
  
}
  

void particle::getAllForces(std::vector<particle>arrayOfAllParticles, int i_tnp){
#pragma omp parallel for   
      for(int i=i_number+1;i<i_tnp;i=i+1){  
	vec_dist = vec_distanceVec(vec_location1,arrayOfAllParticles[i].vec_location1);
	vec_internForce = vec_grav_force_3D(vec_dist, d_mass, arrayOfAllParticles[i].d_mass);
	vec_mainForce = vec_mainForce + vec_internForce;
	arrayOfAllParticles[i].vec_mainForce = arrayOfAllParticles[i].vec_mainForce - vec_internForce;
	vec_internForce.zeros();
      }
      vec_mainAcceleration=(vec_mainForce/d_mass);
}
  


void particle::propagate(double d_timeStep){
  vec_location2 = vec_verlet_step(vec_location0, vec_location1, vec_mainAcceleration, d_timeStep);
  vec_location0 = vec_location1;
  vec_location1 = vec_location2;
}


void particle::setCurrentLocation(arma::vec vec_inLocation){
  vec_location1=vec_inLocation;
}


 void particle::setOldLocation(arma::vec vec_inLocation){
   vec_location0 = vec_inLocation;
   }

   
 void particle::setForce(arma::vec vec_inForce){
   vec_mainForce = vec_inForce;
}

void particle::addToForce(arma::vec vec_inForce){
      vec_mainForce = vec_inForce + vec_mainForce;
}

void particle::calculateAcceleration()
{
vec_mainAcceleration = vec_mainForce/d_mass;
}



arma::vec particle::getCurrentLocation(){
    return vec_location1;
}

arma::vec particle::getOldLocation(){
    return vec_location0;
}

