#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"
#include <cppad/cppad.hpp>

using namespace std;

class MPC {
 public:
  MPC(double ref_v, double latency);

  virtual ~MPC();

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  vector<double> Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);

  vector<double> x_;
  vector<double> y_;
  double ref_v_;
  double latency_;

};

#endif /* MPC_H */
