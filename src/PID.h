#ifndef PID_H
#define PID_H

// for twiddle
#include <vector>
#include <math.h>
#include <iostream>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Variables
  */
  bool is_initialized;
  double prev_cte;
  double int_cte;
  double steer;

  // for twiddle
  int it;
  double err;
  int tw_ctr;
  bool tw_started;
  int index;
  double tol;
  double best_err;
  std::vector<double> params;
  std::vector<double> dp;
  bool increase_dp_index;
  bool decrease_dp_index;
  bool same_dp_index;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();



  // for twiddle
  void Twiddle (double tol);



};

#endif /* PID_H */
