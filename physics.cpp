#include <vector>
#include <armadillo>
#include <cstdlib>
#include <math.h>
#include "physics.h"
#include "particle.h"
#include "newton.h"
#include "vector_operations.h"
#include "dynamics.h"


/* Main function of this library are calculating  potential and kinatic energy as well as adding them up.
   Its planned that, there is at some point in time, the option to save the energys as properties of particles or 
   to save it as one value (more performance oriented). */

double d_getEpot(arma::vec vec_distance, double f_mass1, double f_mass2){
  double gravcon = 66740800000;
  double d_distance;
  d_distance=norm(vec_distance,2);
  return (-1 * (gravcon * f_mass1*f_mass2)/d_distance);
 }

 
