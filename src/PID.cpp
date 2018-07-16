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
}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
	Kp = Kp_;
	Ki = Ki_;
	Kd = Kd_;
	//vector<double>K = [Kp, Ki, Kd];
	//vector<double>dK = [1, 1, 1];
}

void PID::UpdateError(double cte) {
	if (!is_initialized) {
		prev_cte = cte;
		int_cte += cte;
		is_initialized = true;
		return;
	}
	double delta_cte = cte - prev_cte;
	prev_cte = cte;
	int_cte += cte;
	steer = -Kp * cte - Kd * delta_cte - Ki * int_cte;
}

double PID::TotalError() {
}

