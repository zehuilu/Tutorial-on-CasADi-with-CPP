#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <filesystem>
#include <casadi/casadi.hpp>


namespace fs = std::filesystem;


int main(){
    /*  Test problem
     *
     *    min x0^2 + x1^2
     *    s.t.    x0 + x1 - 10 = 0
     */


    // file name
    std::string file_name = "nlp_code";
    // code predix
    std::string prefix_code = fs::current_path().string() + "/";
    // shared library prefix
    std::string prefix_lib = fs::current_path().string() + "/";

    // Create a new NLP solver instance from the compiled code
    std::string lib_name = prefix_lib + file_name + ".so";
    casadi::Function solver = casadi::nlpsol("solver", "ipopt", lib_name);

    // Bounds and initial guess
    std::map<std::string, casadi::DM> arg, res;
    arg["lbx"] = -casadi::DM::inf();
    arg["ubx"] =  casadi::DM::inf();
    arg["lbg"] =  0;
    arg["ubg"] =  casadi::DM::inf();
    arg["x0"] = 0;

    // Solve the NLP
    res = solver(arg);

    // Print solution
    std::cout << "-----" << std::endl;
    std::cout << "objective at solution = " << res.at("f") << std::endl;
    std::cout << "primal solution = " << res.at("x") << std::endl;
    std::cout << "dual solution (x) = " << res.at("lam_x") << std::endl;
    std::cout << "dual solution (g) = " << res.at("lam_g") << std::endl;

    return 0;
}