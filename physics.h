#include <vector>
#include <armadillo>
#include <cstdlib>
#include <math.h>
#include "particle.h"
#include "newton.h"
#include "vector_operations.h"
#include "dynamics.h"

double d_getEpot(arma::vec vec_distance, double f_mass1, double f_mass2);
