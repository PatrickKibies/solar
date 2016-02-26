#include <iostream>
#include <armadillo>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "newton.h"
#include "vector_operations.h"
#include "particle.h"
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
  
   /*
 double f_Force = f_grav_force(f_mSun,f_mEarth,f_r);
  std::cout << "May the force be " << f_Force << std::endl;  
  std::cout << "Sun's accelaration: " << f_acceleration(f_mSun,f_Force) << std::endl;  
  std::cout << "Earth's accelaration: " << f_acceleration(f_mEarth,f_Force) << std::endl;  
  
  arma::vec vect1, vect2; // Define vectors
  vect1.set_size(3); //set size and allocate memory
  vect2.set_size(3);
  vect1.zeros(); //initialize with 0
  vect2.zeros();
  
  //Set some values
  vect1(0) = 149.6e9 * std::cos(3.141);
  vect1(1) = 149.6e9 * std::sin(3.141);
  vect1(2) = 0;
  vect2(2) = 0;
  vect2(1) = 0;
  vect2(0) = 0;
  
  std::cout << "Vectorial calculation of Force:"<<std::endl;
  std::cout << vec_grav_force_3D(vec_distanceVec(vect1,vect2),f_mEarth,f_mSun) << std::endl;
  std::cout << "Force vector norm: " << std::endl;
  std::cout << norm(vec_grav_force_3D(vec_distanceVec(vect1,vect2),f_mEarth,f_mSun)) << std::endl;  
  */
   
  std::vector<particle> arrayOfAllParticles(i_tnp);
  //std::vector <particle*> arrayOfAllParticles;
  //particle *arrayOfAllParticles = new particle[i_tnp];
  
  arrayOfAllParticles[0].createAParticle(0);
  arrayOfAllParticles[0].vec_location0.zeros();
  arrayOfAllParticles[0].vec_location1.zeros();
  arrayOfAllParticles[0].d_mass=d_mSun;
  
  for(int i=1; i<i_tnp;i++){
    arrayOfAllParticles[i].createAParticle(i);
  };
  
  myfile.open ("example.txt");
  for(int step=0; step<i_numTimeSteps;step++){
  
      for(int i=0; i<i_tnp;i++){
	arrayOfAllParticles[i].getAllForces(arrayOfAllParticles, i_tnp);
      };
      
      //myfile.open ("example.txt", std::ios_base::app);
      
      //std::stringstream s;
      //s.append("Hello world, ");
      std::vector<arma::vec> vec_toFile(i_tnp);
      
      //myfile << ",{";
      for(int i=0; i<i_tnp;i++){
	arrayOfAllParticles[i].getNewLocation(i_timeStep);
	//myfile << ",{" ;
	myfile << step << " ";
	for(int j=0; j<3; j++){
	 myfile << arrayOfAllParticles[i].vec_location1(j) << " ";
	}
	myfile << "\n";
	//myfile << "}" ;
	//myfile << ",{" << arrayOfAllParticles[i].vec_location1 << "}" ;
	//vec_toFile[i]=arrayOfAllParticles[i].vec_location1;
	arrayOfAllParticles[i].vec_location0=arrayOfAllParticles[i].vec_location1;
	arrayOfAllParticles[i].vec_location1=arrayOfAllParticles[i].vec_location2;
      };
      //std::string str = s.str();
      //myfile << vec_toFile;
      //myfile << "\n";
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



