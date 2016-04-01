# include <iostream>
# include <string>
# include <vector>
# include "particle.h"
# include <sstream>
# include <vector>
#include "boost/format.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

void makePSF(std::vector<particle> arrayOfAllParticles, int i_tnp);

std::string create_energy_entry(std::vector <particle> particles);

std::string create_amber_line(std::vector <particle> particles);
std::string create_amber_header();

void writePositionXYZ(std::vector<particle> particles, std::string s_filename);
void writeVelocityXYZ(std::vector<particle> &particles, std::string s_filename);

arma::vec readXYZ(std::string s_filename);

std::vector<particle> readParticles(std::string s_velocityFilename, std::string s_positionFilename, std::string s_topologyFilename);


