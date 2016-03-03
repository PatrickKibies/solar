#define _USE_MATH_DEFINES
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

//#include <graphics.h>


int main(int argc, char **argv) {
  double f_mEarth, d_mSun, f_r;
  f_mEarth = 5.972e24;
  d_mSun = 1.989e30;
  f_r = 149.6e9;
  int i_tnp=2; //total number of particels
  int i_numTimeSteps=10000; //Number of time steps
  int i_timeStep=3600*24; //in [s]
  
  std::ofstream myfile, file_trajectory;
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
  arrayOfAllParticles[1].vec_location0(0) = f_r;
  arrayOfAllParticles[1].vec_location1 = arrayOfAllParticles[1].vec_location0;
  arrayOfAllParticles[1].vec_location1(1) = 30e3 * i_timeStep;
  arrayOfAllParticles[1].d_mass=f_mEarth;
  
 /* for(int i=1; i<i_tnp;i++){
    arrayOfAllParticles[i].createAParticle(i);
  };*/
  
  
  makePSF(arrayOfAllParticles, i_tnp);

  myfile.open ("example.txt");
  file_trajectory.open("output.crd");
  file_trajectory << create_amber_header();
  file_trajectory << create_amber_line(arrayOfAllParticles);
  
  for(int step=0; step<i_numTimeSteps;step++){// Time Step loop
	  
    for (int i_parti = 0; i_parti < i_tnp; i_parti++){
      
      arrayOfAllParticles[i_parti].vec_mainForce.zeros(); //set all Forces to 0,0,0 for new timestep!
      
    }
    
    
    
    for(int i=0; i<i_tnp;i++){  //Outer Force calculation loop over all particles
      for (int jj = i+1; jj<i_tnp; jj++){
	  
//	  std::cout << "Calculating force between " << i << " and " << jj;
	  
	  
	  arma::vec temp_force;
	  temp_force.set_size(3);
	  temp_force.zeros();
	  
	  temp_force = vec_grav_force_3D(vec_distanceVec(arrayOfAllParticles[i].getCurrentLocation(),arrayOfAllParticles[jj].getCurrentLocation()),arrayOfAllParticles[i].d_mass,arrayOfAllParticles[jj].d_mass);
	  arrayOfAllParticles[i].addToForce(-temp_force);
	  arrayOfAllParticles[jj].addToForce(temp_force);
	}

      };
      
      
      for(int i=0; i<i_tnp;i++){
	arrayOfAllParticles[i].calculateAcceleration();
	arrayOfAllParticles[i].propagate(i_timeStep);
	
  	myfile << step << " ";
	
	for(int j=0; j<3; j++){
	 myfile << arrayOfAllParticles[i].vec_location1(j) << " ";
	}
	myfile << "\n";
    }
	
    
    file_trajectory << create_amber_line(arrayOfAllParticles);  
}
  myfile.close();
  file_trajectory.close();
  std::cout << "Position of the first Particle:" << std::endl;
  std::cout << arrayOfAllParticles[0].vec_location1 << std::endl;
  std::cout << "Main force vector of the first Particle:" << std::endl;
  std::cout << arrayOfAllParticles[0].vec_mainForce << std::endl;
  std::cout << "Main accelaration vector of the first Particle:" << std::endl;
  std::cout << arrayOfAllParticles[0].vec_mainAcceleration << std::endl;
  return 0;
}
