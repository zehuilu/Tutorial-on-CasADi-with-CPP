#include <iostream>
#include <string>
#include <filesystem>
#include <casadi/casadi.hpp>


namespace fs = std::filesystem;


int main(){
    // symbolic variables
    casadi::SX posi = casadi::SX::sym("p", 2);
    casadi::SX posi_des = casadi::SX::sym("p_des", 2);

    // objective function
    casadi::SX fun_obj = pow(posi(0)-posi_des(0), 2) +
                         pow(posi(1)-posi_des(1), 2);
    // gradients
    casadi::SX fun_obj_grad = jacobian(fun_obj, posi);  // 1 by 2 jacobian matrix

    // functions to be generated
    casadi::Function f_fun_obj("fun_obj", {posi, posi_des}, {fun_obj});
    casadi::Function f_fun_obj_grad("fun_obj_grad", {posi, posi_des}, {fun_obj_grad});


    // options for c-code auto generation
    casadi::Dict opts = casadi::Dict();
    opts["cpp"] = false;
    opts["with_header"] = true;
    // prefix for c code
    std::string prefix_code = fs::current_path().parent_path().string() + "/code_gen/";

    // generate functions in c code
    casadi::CodeGenerator myCodeGen = casadi::CodeGenerator("example.c", opts);
    myCodeGen.add(f_fun_obj);
    myCodeGen.add(f_fun_obj_grad);

    myCodeGen.generate(prefix_code);

    // compile c code to a shared library
    std::string prefix_lib = fs::current_path().parent_path().string() + "/build/";
    std::string compile_command = "gcc -fPIC -shared -O3 " + 
        prefix_code + "example.c -o " +
        prefix_lib + "lib_example.so";

    std::cout << compile_command << std::endl;

    int compile_flag = std::system(compile_command.c_str());
    casadi_assert(compile_flag==0, "Compilation failed!");
    std::cout << "Compilation successed!" << std::endl;

    return 0;
}