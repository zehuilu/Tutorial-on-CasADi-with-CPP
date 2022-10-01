# Tutorial-on-CasADi-with-CPP
This is a Tutorial on how to use CasADi with CPP.


This repo has been tested with:
* GCC 11.1.0, CMake 3.16.3, Ubuntu 20.04.5 LTS


I recommend going through the CasADi's [official documentation](https://web.casadi.org/docs/) first, then come to this repo to learn about how to use CasADi with C++.
Even though the offical documentation focuses on CasADi's usage in Python and MATLAB, there are a lot of concepts you can borrow from them when coding CasADi in C++.



Dependency
==========

* [ipopt](https://coin-or.github.io/Ipopt/)
* [CasADi](https://web.casadi.org/)


The instructions for dependency installation is shown below.


For Linux
```
$ sudo apt update
$ sudo apt install build-essential
$ sudo apt install coinor-libipopt-dev
$ pip3 install casadi
```


Instructions on upgrade GCC to Version 11
```
$ sudo apt install manpages-dev software-properties-common
$ sudo add-apt-repository ppa:ubuntu-toolchain-r/test
$ sudo apt update && sudo apt install gcc-11 g++-11
$ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 110
$ sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 110
```

To check GCC's version
```
$ gcc --version
$ g++ --version
```



Build
=====

To build casadi from source, see instructions [here](https://github.com/casadi/casadi/wiki/InstallationLinux).
```
$ sudo apt install gfortran liblapack-dev pkg-config --install-recommends
$ sudo apt install swig
$ cd
$ git clone https://github.com/casadi/casadi.git -b master casadi
$ cd casadi
$ mkdir build
$ cd build
$ cmake -DWITH_PYTHON=ON -DWITH_IPOPT=ON ..
$ make
$ sudo make install
```


To build this repo,
```
$ cd
$ git clone https://github.com/zehuilu/Tutorial-on-CasADi-with-CPP.git
$ cd <MAIN_DIRECTORY>
$ mkdir code_gen
$ cd build
$ cmake ..
$ make
```



Example
=======

1. See how CasADi and IPOPT work together to solve a [race car example](https://web.casadi.org/blog/ocp/),
```
$ cd <MAIN_DIRECTORY>/build
$ ./example_racecar
```


2. See some basic operations in CasADi,
```
$ cd <MAIN_DIRECTORY>/build
$ ./example_basic_operations
```


3. See how to automatically generate functions in C code, and how to use them in another C++ file.

First, compile a file to generate C code automatically, and run it to compile these C codes as a shared library.
```
$ cd <MAIN_DIRECTORY>/build
$ ./example_code_gen
```

Secondly, re-run the cmake command to compile another C++ file to use the aforementioned shared library.
```
$ cmake ..
$ make
$ ./example_use_code_gen
```


If you want to know how to evoke other operations or functions via CasADi in C++, feel free to post your questions/requests in Issues or Discussions.
