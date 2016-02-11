#include <armadillo>

void void_verlet_step(arma::vec &vec_oldPosition, arma::vec &vec_currentPosition, arma::vec &vec_acceleration, arma::vec &vec_newPosition, const double &f_timestep){
  vec_newPosition = 2*vec_currentPosition - vec_oldPosition + f_timestep * f_timestep * vec_acceleration;
}

arma::vec vec_verlet_step(arma::vec& vec_oldPosition, arma::vec& vec_currentPosition, arma::vec& vec_acceleration, const double f_timestep){
  return (2.*vec_currentPosition) - vec_oldPosition + (f_timestep * f_timestep * vec_acceleration);
}

arma::vec vec_positionVelocity(arma::vec &vec_oldPosition, arma::vec &vec_velocity, double f_timestep){
  return vec_oldPosition + (vec_velocity * f_timestep);
}