#include <iostream>
#include <string>
#include <casadi/casadi.hpp>


int main(){
    // create a symbolic vector
    casadi::SX q = casadi::SX::sym("q", 7);
    std::cout << "q: " << q << std::endl;

    casadi::SX q2 = casadi::SX::sym("q2", 7);
    std::cout << "q2: " << q2 << std::endl;

    // horizontally stack
    casadi::SX qh = horzcat(q, q2);
    std::cout << "horizontally stack q and q2: " << qh << std::endl;

    // vertically stack
    casadi::SX qv = vertcat(q, q2);
    std::cout << "vertically stack q and q2: " << qv << std::endl;

    // transpose
    casadi::SX qt = transpose(qh);
    std::cout << "transpose of qh: " << qt << std::endl;

    // create symbolic vectors and change values
    casadi::SX t1 = casadi::SX::sym("t1", 3);
    t1(0) = 0;
    t1(1) = 0;
    t1(2) = 0.1564;
    casadi::SX t2 = casadi::SX::zeros(3, 1);
    t2(1) = 0.0054;
    t2(2) = -0.1284;

    std::cout << "t1: " << t1 << std::endl;
    std::cout << "t2: " << t2 << std::endl;

    // create a symbolic matrix
    casadi::SX T01 = casadi::SX::zeros(4, 4);

    // slicing operation

    // casadi::Slice a01(0, 3, 1); // start index, stop (not included) index, step
    // slice the first to the third element in the forth row as a new vector
    T01(casadi::Slice(0, 3, 1), 3) = t1;
    T01(3, 3) = 1;
    T01(2, 2) = -1;
    T01(0, 0) = cos(q(0)); // NOTE: functions like cos() in casadi don't use casadi::
    T01(0, 1) = -sin(q(0));
    T01(1, 0) = -sin(q(0));
    T01(1, 1) = -cos(q(0));
    std::cout << "T01: " << T01 << std::endl;

    casadi::SX T12 = casadi::SX::zeros(4, 4);
    T12(casadi::Slice(0, 3, 1), 3) = t2;
    T12(3,3) = 1;
    T12(1, 2) = -1;
    T12(0, 0) = cos(q(1));
    T12(0, 1) = -sin(q(1));
    T12(2, 0) = sin(q(1));
    T12(2, 1) = cos(q(1));
    std::cout << "T12: " << T12 << std::endl;

    // test matrix multiplication
    casadi::SX _A = casadi::SX::zeros(2, 2);
    _A(0,0) = 100;
    _A(0,1) = 50;
    _A(1,0) = -1;
    _A(1,1) = -2;
    casadi::SX _B = casadi::SX::zeros(2, 2);
    _B(0,0) = 0.5;
    _B(0,1) = 0.1;
    _B(1,0) = 0.2;
    _B(1,1) = 0.4;
    std::cout << "test matrix multiplication: " << std::endl;
    std::cout << "_A: " << _A << std::endl;
    std::cout << "_B: " << _B << std::endl;
    std::cout << "element-wise multiplication: " << _A * _B << std::endl;
    std::cout << "matrix multiplication: " << mtimes(_A, _B) << std::endl; // NOTE: mtime() in casadi don't use casadi::

    casadi::SX T1 = T01;
    casadi::SX T2 = mtimes(T1, T12);

    std::cout << "T1: " << T1 << std::endl;
    std::cout << "T2: " << T2 << std::endl;

    return 0;
}