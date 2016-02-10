#include <armadillo>

void void_verlet_step(arma::vec &vec_oldPosition, arma::vec &vec_currentPosition, arma::vec &vec_acceleration, arma::vec &vec_newPosition, const double &f_timestep);
arma::vec vec_verlet_step(arma::vec vec_oldPosition, arma::vec vec_currentPosition, arma::vec vec_acceleration, const double f_timestep);
//arma::vec vec_verlet_step(arma::vec& vec_oldPosition, arma::vec& vec_currentPosition, arma::vec& vec_acceleration, const double& f_timestep);
arma::vec vec_positionVelocity(arma::vec &vec_oldPosition, arma::vec &vec_velocity, double timestep);