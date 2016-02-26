#ifndef PARTICLE_H
#define PARTICLE_H
#include <armadillo>
#include <vector>

class particle
{
  public:
    arma::vec vec_location0,vec_location1, vec_location2;
    arma::vec vec_speed0,vec_speed1,vec_speed2;
    arma::vec vec_mainForce;
    arma::vec vec_internForce;
    arma::vec vec_mainAcceleration;
    float f_massFactor;
    float f_massPower;
    double d_mass;
    int i_number;
    float f_radius;
   
    
    void createAParticle(int number); //creates a particle as an object
    
    long l_min;
    long l_max;
    long l_randomNr;
    arma::vec vec_dist;
    
    void getAllForces(std::vector<particle>arrayOfAllParticles, int i_tnp);	/* calculates the force vectors to all other particles 
										   and summs them up. The acceleration is calculed from 
										   this main force vector */
										   
    void getNewLocation(int i_timeStep);
										   
 private: int i_potenz;
	  float f_prefactor;

};   
    


/*
class particle
{
public:
    void createAParticle(int number);
};
*/

#endif // PARTICLE_H
