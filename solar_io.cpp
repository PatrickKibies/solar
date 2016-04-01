# include <iostream>
# include <string>
# include <istream>
# include <sstream>
# include <vector>
# include "particle.h"
# include "boost/format.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
//    1231 !NATOM
//       1 U    1    MET  N    NH3   -0.300000       14.0070           0


std::ofstream psfFile;

void makePSF(std::vector<particle> arrayOfAllParticles, int i_tnp){ //Thisroutine does not produce valid PSF files - let's redo that with boost::format

//boost::format format_psf_Line(" %1d %2$3s %3$4d %4$7s %5$4s %6$4s %7$9.6f %8$9.4s %11d");
boost::format format_psf_Line(" %7d %-5s%-5d%-5s%-5s%-5s %3.6f%9.4s%11d");    
  
  
psfFile.open ("test.psf");
psfFile << "PSF CMAP" << std::endl; //Write header line  of PSF file
psfFile << i_tnp << " !NATOM" << std::endl; // Write 

for(int i=0; i<i_tnp;i++){
  //psfFile << " "<< arrayOfAllParticles[i].i_number << " U    1    MET  N    NH3 " << arrayOfAllParticles[i].f_radius << arrayOfAllParticles[i].d_mass << " 0" << std::endl;
  psfFile << format_psf_Line % i % "U" % 1 % "MET" % "N" % "N" %   arrayOfAllParticles[i].f_radius % arrayOfAllParticles[i].d_mass % 0 << std::endl; 
  
}

psfFile.close();

}

std::string create_energy_entry(std::vector <particle> particles){
  boost::format fmt_string("%1$8.3f ");
  std::string ssEpot_temp;
  uint i_particleCount = particles.size();
  for (uint ii = 0; ii < i_particleCount; ii++){
    fmt_string % (particles[ii].d_Epot);
    ssEpot_temp.append(fmt_string.str());;
  }
  ssEpot_temp.append("\n");
  return ssEpot_temp;
}


std::string create_amber_line(std::vector <particle> particles){ // The whole stringstream business is not working right now - but formatting works. Maybe I shall switch to plain strings.
  
  uint i_particleCount = particles.size();
  std::string ss_temp;
  int count_linemembers = 0; 
  boost::format fmt_string("%1$8.3f ");
  
  
  for (uint ii = 0; ii < i_particleCount; ii++){  
    for (uint jj = 0; jj <particles[ii].vec_location1.size(); jj++){
      count_linemembers++;
     
    if(jj<particles[ii].vec_location1.size()){
      //fmt_string % (particles[ii].vec_location1[jj]/149e9);
      fmt_string % (particles[ii].vec_location1[jj]/1e2); //Division is needed to make the coordinates suitable for VMD
      ss_temp.append(fmt_string.str());
    }
  
    if (count_linemembers >=10){
	ss_temp.append("\n");
	count_linemembers = 0;
	}
     }
  }
  //ss_temp.append("\n");
  return ss_temp;
}

std::string create_amber_header()
{
return "Solar greetz!\n";
}

void writePositionXYZ(std::vector<particle> particles, std::string s_filename){
  
  std::ofstream file_outXYZ;
  file_outXYZ.open(s_filename.c_str());
  std::string s_xyzline;
  boost::format fmt_xyzline("%1$s %2$10.6f %3$10.6f %4$10.6f");
  arma::vec vec_location;
  
  for(int ii = 0; ii<particles.size(); ii++){
     vec_location = particles[ii].vec_location1;
    fmt_xyzline %particles[ii].s_type % vec_location(0) % vec_location(1) % vec_location(2);
    file_outXYZ << fmt_xyzline.str() <<std::endl;
        
  }

  file_outXYZ.close();
}

void writeVelocityXYZ(std::vector<particle> &particles, std::string s_filename){
  
}

arma::vec readXYZ(std::string s_filename){
  
}

std::vector<particle> readParticles(std::string s_velocityFilename, std::string s_positionFilename, std::string s_topologyFilename){
  
}
