#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {
  is_initialized = false;
  Kp = 0.0;
  Ki = 0.0;
  Kd = 0.0;

  prev_cte = 0.0;
  int_cte = 0.0;
  steer = 0.0;

  // for twiddle
  it = 0;
  err = 0.0;
  tw_ctr = 100;
  index = 3;
  tol = 0.0001;
  best_err = 0.0;
  params = {0., 0., 0.};
  dp = {0.1, 0.1, 0.1};
  // dp = {1.0, 1.0, 1.0};
  tw_started = false;
  increase_dp_index = false;
  decrease_dp_index = false;
  same_dp_index = false;
}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
	Kp = Kp_;
	Ki = Ki_;
	Kd = Kd_;

	p_error = 0.0;
	i_error = 0.0;
	d_error = 0.0;
}

void PID::UpdateError(double cte) {
	d_error = cte - p_error;
	p_error = cte;
	// to make sure that the integral doesn't add value when cte is already == 0
	// another option: setting a max value for i_error so it doesn't accumulate too much
	if (cte > 0.0001)
		i_error += cte;
	else
		i_error = 0;
	if (fabs(i_error) > 40)
		i_error = 0;
	
	err = pow(cte, 2);

	// for twiddle
	// if (it >= tw_ctr) 
	// 	Twiddle (tol);
}

double PID::TotalError() {
	return Kp * p_error + Ki * i_error + Kd * d_error;
}

void PID::Twiddle (double tol) {
	double sum = 0.0;
	for (auto &d : dp) sum += d;
	if (sum > tol) {
		// for the initial best_err
		if ((it == tw_ctr) || !tw_started) {
			params[index] += dp[index];
			best_err = err;
			std::cout << "New twiddle" << std::endl;
			tw_started = true;
			return;
		}
		if (it > tw_ctr) {
			if (best_err > err) {
				best_err = err;
				dp[index] *= 1.1;
				increase_dp_index = true;
				decrease_dp_index = false; 
				std::cout << "Increase twiddle" << std::endl;
			} 
			else {
				decrease dp index
				if (!decrease_dp_index) {
					params[index] -= 2.0 * dp[index];
					//increase_dp_index = true;
					decrease_dp_index = true;
					// same_dp_index = true;
					std::cout << "Decrease twiddle" << std::endl;
				} else {
					// dp index remains the same
                    params[index] += dp[index];
                    dp[index] *= 0.9;					
					//increase_dp_index = true;
					decrease_dp_index = false;
					same_dp_index = true;
					std::cout << "Same twiddle" << std::endl;
				}
			}
		}
		// to write out in main
		Kp = params[0];
		Kd = params[1];
		Ki = params[2];

		if (!decrease_dp_index && same_dp_index) {
			std::cout << "Change index" << std::endl;
			index = (index + 1) % 3;
			increase_dp_index = false;
			decrease_dp_index = false;
			same_dp_index = false;
			tw_started = false;
		}
	}
}
