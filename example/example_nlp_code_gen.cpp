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

    // Optimization variables
    casadi::MX x = casadi::MX::sym("x", 2);

    // Objective
    casadi::MX f = x(0)*x(0) + x(1)*x(1);

    // Constraints
    casadi::MX g = x(0)+x(1)-10;

    // Create an NLP solver instance
    casadi::Function solver = casadi::nlpsol("solver", "ipopt", {{"x", x}, {"f", f}, {"g", g}});

    // file name
    std::string file_name = "nlp_code";
    // code predix
    std::string prefix_code = fs::current_path().string() + "/";

    // Generate C code for the NLP functions
    solver.generate_dependencies(file_name + ".c");

    // shared library prefix
    std::string prefix_lib = fs::current_path().string() + "/";

    // compile c code to a shared library
    std::string compile_command = "gcc -fPIC -shared -O3 " + 
        prefix_code + file_name + ".c -o " +
        prefix_lib + file_name + ".so";

    std::cout << compile_command << std::endl;
    int compile_flag = std::system(compile_command.c_str());
    casadi_assert(compile_flag==0, "Compilation failed");
    std::cout << "Compilation successed!" << std::endl;

    return 0;
}