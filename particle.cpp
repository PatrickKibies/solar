
// #include "particle.h"
#include <vector>
#include <armadillo>
#include <cstdlib>
#include "particle.h"
#include "newton.h"
#include "vector_operations.h"
  

  
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
  
  float mass_LO=1.0;
  float mass_HI=9.9;
  //std::srand(42);
  f_massPower =20 + (std::rand() % (int)(25 - 20 + 1));
  f_massFactor= mass_LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(mass_HI-mass_LO)));
  d_mass=f_massFactor*pow(10,f_massPower);
  
  i_number=number;

  float LO=-9.0;
  float HI=9.0;
  
  for(int j=0;j<3;j++){
    //std::srand(42); 
    // Merkur <-> Sonne 46,0 x 10⁶ km
    // Pluto <-> Sonne 7,48*10⁹ km
    
    i_potenz=9 + (std::rand() % (int)(12 - 9 + 1));
    f_prefactor = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    vec_location1(j)=f_prefactor*pow(10,i_potenz);
    vec_location0(j)=vec_location1(j)+(-30 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(30-(-30)))))*1000;
  };
};
  

void particle::getAllForces(std::vector<particle>arrayOfAllParticles, int i_tnp){
    
      for(int i=i_number+1;i<i_tnp;i=i+1){  
	vec_dist = vec_distanceVec(vec_location1,arrayOfAllParticles[i].vec_location1);
	vec_internForce = vec_grav_force_3D(vec_dist, d_mass, arrayOfAllParticles[i].d_mass);
	vec_mainForce = vec_mainForce + vec_internForce;
	arrayOfAllParticles[i].vec_mainForce = arrayOfAllParticles[i].vec_mainForce - vec_internForce;
	vec_internForce.zeros();
      };
      vec_mainAcceleration=vec_mainForce/d_mass;
};
  
void particle::getNewLocation(int i_timeStep){
    vec_location2 = 2*vec_location1 - vec_location0 + vec_mainAcceleration*pow(i_timeStep,2);
};
   
