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
  d_mSun = 1.989*pow(10,30);
  f_r = 149.6e9;
  int i_tnp=20; //total number of particels
  int i_numTimeSteps=1000; //Number of time steps
  int i_timeStep=31536; //in [s]
  
  std::ofstream myfile;
  std::vector<particle> arrayOfAllParticles(i_tnp);
  
  arrayOfAllParticles[0].createAParticle(0);
  arrayOfAllParticles[0].vec_location0.zeros();
  arrayOfAllParticles[0].vec_location1.zeros();
  arrayOfAllParticles[0].d_mass=d_mSun;
  
  for(int i=1; i<i_tnp;i++){
    arrayOfAllParticles[i].createAParticle(i);
  };
  
  makePSF(arrayOfAllParticles, i_tnp);
  
  myfile.open ("example.txt");
  for(int step=0; step<i_numTimeSteps;step++){
  
      for(int i=0; i<i_tnp;i++){
	arrayOfAllParticles[i].getAllForces(arrayOfAllParticles, i_tnp);
      };
      
      std::vector<arma::vec> vec_toFile(i_tnp);
      
  
      for(int i=0; i<i_tnp;i++){
	arrayOfAllParticles[i].getNewLocation(i_timeStep);
	myfile << step << " ";
	for(int j=0; j<3; j++){
	 myfile << arrayOfAllParticles[i].vec_location1(j) << " ";
	}
	myfile << "\n";
	arrayOfAllParticles[i].vec_location0=arrayOfAllParticles[i].vec_location1;
	arrayOfAllParticles[i].vec_location1=arrayOfAllParticles[i].vec_location2;
      };
  };
  myfile.close();
  
  std::cout << "Position of the first Particle:" << std::endl;
  std::cout << arrayOfAllParticles[0].vec_location1 << std::endl;
  std::cout << "Main force vector of the first Particle:" << std::endl;
  std::cout << arrayOfAllParticles[0].vec_mainForce << std::endl;
  std::cout << "Main accelaration vector of the first Particle:" << std::endl;
  std::cout << arrayOfAllParticles[0].vec_mainAcceleration << std::endl;

  return 0;
}
