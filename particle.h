#ifndef PARTICLE_H
#define PARTICLE_H
#include <armadillo>
#include <vector>
#include "dynamics.h"
#include "physics.h"

/**
\class particle
The class particle contains all functionality concerning a single particle. It provides methods and attributes to get all relevant data and manipulations to a particle (i.e. calculating the forces or do a verlet integration step)
*/




class particle
{
  public:
    arma::vec vec_location0,vec_location1, vec_location2; //* Position holding vectors
    arma::vec vec_speed0,vec_speed1,vec_speed2; //* velocity holding vectors
    arma::vec vec_mainForce; //* Holds the mean force the particle experiences
    arma::vec vec_internForce; //* ????
    arma::vec vec_mainAcceleration; //* Mean acceleration of this particle
    float f_massFactor;
    float f_massPower;
    double d_mass;
    double d_Epot;
    double d_intern_Epot;
    double d_Ekin;
    int i_number;
    float f_radius;
    std::string s_type;
    
    void createAParticle(int number); //creates a particle as an object
    
    long l_min;
    long l_max;
    long l_randomNr;
    arma::vec vec_dist;
    
    void getAllForces(std::vector<particle>arrayOfAllParticles, int i_tnp);	//* calculates the force vectors to all other particles  and sums them up. The acceleration is calculated from this main force vector
    void propagate(double d_timeStep); //* Performs a verlet time step for this particle
    void setCurrentLocation(arma::vec vec_setLocation); 
    void setOldLocation(arma::vec vec_setLocation);
    void setForce(arma::vec vec_inForce);
    void addToForce(arma::vec vec_inForce);
    void setEpot(double vec_inEpot);
    void addToEpot(double vec_inEpot);
    void calculateAcceleration(); //* This method calculates the current acceleration from the current force vector and the particles mass
    arma::vec getCurrentLocation();
    arma::vec getOldLocation();
    
										   
 private: int i_potenz;
	  float f_prefactor;

};   
    

#endif // PARTICLE_H
