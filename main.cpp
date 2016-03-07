#define _USE_MATH_DEFINES
#include <boost/timer/timer.hpp>
#include <iostream>
#include <armadillo>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


#include "newton.h"
#include "vector_operations.h"
#include "particle.h"
#include "dynamics.h"
#include <math.h>
#include "solar_io.h"
#include "physics.h"

//#include <graphics.h>


int main(int argc, char **argv) {
  //Internal units: 
  //Length in 1e9 m
  //Mass in 1e21 kg
  //Time in 1e15 s
  
  double d_mEarth, d_mSun, d_r;
  d_mEarth = 5972000; //in Yg
  d_mSun = 1989000000000; //in Yg
  d_r = 149.5978707; //in Gm
  int i_tnp=6; //total number of particels
  int i_numTimeSteps=10000; //Number of time steps
  double d_timeStep=0.00000000008640; //in [Ps]
  
  std::ofstream myfile, file_trajectory, energies;
  std::vector<particle> arrayOfAllParticles(i_tnp);
  arma::vec vec_zerovec;
  vec_zerovec.set_size(3);
  vec_zerovec.zeros();
  
  arrayOfAllParticles[0].createAParticle(0);
  arrayOfAllParticles[0].vec_location0.zeros();
  arrayOfAllParticles[0].vec_location1.zeros();
  arrayOfAllParticles[0].d_mass=d_mSun;
  
  
  arrayOfAllParticles[1].createAParticle(1);
  arrayOfAllParticles[1].vec_location0.zeros();
  arrayOfAllParticles[1].vec_location1.zeros();
  arrayOfAllParticles[1].vec_location0(0) = d_r;
  arrayOfAllParticles[1].vec_location1 = arrayOfAllParticles[1].vec_location0;
  arrayOfAllParticles[1].vec_location1(1) = 29848324764.9708 * d_timeStep;
  arrayOfAllParticles[1].d_mass=d_mEarth;
  
  arrayOfAllParticles[2].createAParticle(1);
  arrayOfAllParticles[2].vec_location0.zeros();
  arrayOfAllParticles[2].vec_location1.zeros();
  arrayOfAllParticles[2].vec_location0(0) = d_r+0.3844;
  arrayOfAllParticles[2].vec_location1 = arrayOfAllParticles[2].vec_location0;
  arrayOfAllParticles[2].vec_location1(1) = (29848324764.9708 - 1018272263.03427) * d_timeStep;
  arrayOfAllParticles[2].d_mass=73490;
  
  for(int i=3; i<i_tnp;i++){
    arrayOfAllParticles[i].createAParticle(i);
  }
  
  
  makePSF(arrayOfAllParticles, i_tnp);

  myfile.open ("example.txt");
  energies.open ("energies.txt");
  file_trajectory.open("output.crd");
  file_trajectory << create_amber_header();
  file_trajectory << create_amber_line(arrayOfAllParticles);
  
  
  for(int step=0; step<i_numTimeSteps;step++){// Time Step loop
	 // boost::timer::auto_cpu_timer t;
    for (int i_parti = 0; i_parti < i_tnp; i_parti++){
      
      arrayOfAllParticles[i_parti].vec_mainForce.zeros(); //set all Forces to 0,0,0 for new timestep!
      arrayOfAllParticles[i_parti].d_Epot=0; //set potential energy to 0 for new timestep!
      
    }
    
    
    
    for(int i=0; i<i_tnp;i++){  //Outer Force calculation loop over all particles
#pragma openmp parallel for
      for (int jj = i+1; jj<i_tnp; jj++){  
	//  std::cout << "Calculating force between " << i << " and " << jj << std::endl; 
	  arma::vec temp_force;
	  arma::vec temp_dist;
	  temp_force.set_size(3);
	  temp_force.zeros();
	  temp_dist.set_size(3);
	  temp_dist.zeros();
	  double temp_Epot;
	  temp_Epot=0;
	  
	  temp_dist = vec_distanceVec(arrayOfAllParticles[i].getCurrentLocation(),arrayOfAllParticles[jj].getCurrentLocation());
	  temp_force = vec_grav_force_3D(temp_dist,arrayOfAllParticles[i].d_mass,arrayOfAllParticles[jj].d_mass);
	  arrayOfAllParticles[i].addToForce(-temp_force);
	  arrayOfAllParticles[jj].addToForce(temp_force);
	  temp_Epot = d_getEpot(temp_dist, arrayOfAllParticles[i].d_mass,arrayOfAllParticles[jj].d_mass);
	  arrayOfAllParticles[i].addToEpot(temp_Epot);
	  arrayOfAllParticles[jj].addToEpot(temp_Epot);
	}
      };
      
      
      for(int i=0; i<i_tnp;i++){
	arrayOfAllParticles[i].calculateAcceleration();
	arrayOfAllParticles[i].propagate(d_timeStep);
	
  	myfile << step << " ";
	
	for(int j=0; j<3; j++){
	 myfile << arrayOfAllParticles[i].vec_location1(j) << " ";
	}
	myfile << "\n";
    }
	
    
    file_trajectory << create_amber_line(arrayOfAllParticles);
    energies << create_energy_entry(arrayOfAllParticles);
}
  myfile.close();
  file_trajectory.close();
  energies.close();
  
  /*
  std::cout << "Position of the first Particle:" << std::endl;
  std::cout << arrayOfAllParticles[0].vec_location1 << std::endl;
  std::cout << "Main force vector of the first Particle:" << std::endl;
  std::cout << arrayOfAllParticles[0].vec_mainForce << std::endl;
  std::cout << "Main accelaration vector of the first Particle:" << std::endl;
  std::cout << arrayOfAllParticles[0].vec_mainAcceleration << std::endl;
  */
  
  return 0;
}
