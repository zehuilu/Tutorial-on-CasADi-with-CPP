#include <iostream>
#include <casadi/casadi.hpp>


// dx/dt = f(x,u)
casadi::MX f(const casadi::MX& x, const casadi::MX& u) {
  return vertcat(x(1), u-x(1));
}

int main(){
  // Car race along a track
  // ----------------------
  // An optimal control problem (OCP),
  // solved with direct multiple-shooting.
  //
  // For more information see: http://labs.casadi.org/OCP

  int N = 100; // number of control intervals

  casadi::Opti opti = casadi::Opti(); // Optimization problem

  casadi::Slice all;
  // ---- decision variables ---------
  casadi::MX X = opti.variable(2, N + 1); // state trajectory
  auto pos = X(0, all);
  auto speed = X(1, all);
  casadi::MX U = opti.variable(1, N); // control trajectory (throttle)
  casadi::MX T = opti.variable(); // final time

  // ---- objective          ---------
  opti.minimize(T); // race in minimal time

  // ---- dynamic constraints --------
  casadi::MX dt = T / N;
  for (int k = 0; k < N; ++k) {
    casadi::MX k1 = f(X(all,k),         U(all,k));
    casadi::MX k2 = f(X(all,k)+dt/2*k1, U(all,k));
    casadi::MX k3 = f(X(all,k)+dt/2*k2, U(all,k));
    casadi::MX k4 = f(X(all,k)+dt*k3,   U(all,k));
    casadi::MX x_next = X(all,k) + dt/6*(k1+2*k2+2*k3+k4);
    opti.subject_to(X(all,k+1)==x_next); // close the gaps 
  }

  // ---- path constraints -----------
  opti.subject_to(speed<=1-sin(2*casadi::pi*pos)/2); // track speed limit
  opti.subject_to(0<=U<=1);           // control is limited

  // ---- boundary conditions --------
  opti.subject_to(pos(0)==0);   // start at position 0 ...
  opti.subject_to(speed(0)==0); // ... from stand-still 
  opti.subject_to(pos(N)==1); // finish line at position 1

  // ---- misc. constraints  ----------
  opti.subject_to(T>=0); // Time must be positive

  // ---- initial values for solver ---
  opti.set_initial(speed, 1);
  opti.set_initial(T, 1);

  // ---- solve NLP              ------
  opti.solver("ipopt"); // set numerical backend
  casadi::OptiSol sol = opti.solve();   // actual solve

  return 0;
}