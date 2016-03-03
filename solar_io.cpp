# include <iostream>
# include <string>
# include <istream>
# include <sstream>
# include <vector>
# include "particle.h"
# include "boost/format.hpp"

//    1231 !NATOM
//       1 U    1    MET  N    NH3   -0.300000       14.0070           0


std::ofstream psfFile;

void makePSF(std::vector<particle> arrayOfAllParticles, int i_tnp){ //Thisroutine does not produce valid PSF files - let's redo that with boost::format

psfFile.open ("test.psf");
psfFile << "PSF CMAP" << std::endl;


psfFile << i_tnp << " !NATOM" << std::endl;

for(int i=0; i<i_tnp;i++){
  psfFile << " "<< arrayOfAllParticles[i].i_number << " U    1    MET  N    NH3 " << arrayOfAllParticles[i].f_radius << arrayOfAllParticles[i].d_mass << " 0" << std::endl;
}

psfFile.close();

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
      fmt_string % (particles[ii].vec_location1[jj]/149e9);
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

