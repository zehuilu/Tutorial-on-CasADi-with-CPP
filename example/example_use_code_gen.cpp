#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <filesystem>
#include <casadi/casadi.hpp>


namespace fs = std::filesystem;


int main(){
    // input
    std::vector<double> posi(2, 0);
    posi[0] = 10.0;
    posi[1] = 5.0;

    std::vector<double> posi_des(2, 0);
    posi_des[0] = 5.0;
    posi_des[1] = 3.0;

    std::vector<casadi::DM> arg_1 = {casadi::DM(posi), casadi::DM(posi_des)};


    // library prefix and full name
    std::string prefix_lib = fs::current_path().parent_path().string() + "/build/";
    std::string lib_full_name = prefix_lib + "lib_example.so";

    // use this function
    casadi::Function fun_obj = casadi::external("fun_obj", lib_full_name);
    casadi::Function fun_obj_grad = casadi::external("fun_obj_grad", lib_full_name);

    // compute objective function
    std::vector<casadi::DM> result_1 = fun_obj(arg_1);
    // the first result
    std::cout << "objective function: " << result_1.at(0) << std::endl;


    // another way to input
    std::vector<casadi::DM> arg_2 = {posi, posi_des};

    // compute objective function jacobian
    std::vector<casadi::DM> result_2 = fun_obj_grad(arg_2);
    // the first result
    std::cout << "objective function jacobian: " << result_2.at(0) << std::endl;

    return 0;
}