# Scientific Computing

In this personal project I implement in C++ the numerical solution of some famous mathematical models.

The models implemented are:
- The [Lotka-Volterra](https://en.wikipedia.org/wiki/Lotka%E2%80%93Volterra_equations) model
- [Finite Element Method](https://en.wikipedia.org/wiki/Finite_element_method) in one dimension 

## Compilation
To compile `scicomp` the C++ version must be greater than 17.
CMake is used to create the makefile. The only dependency is to have an installation of Python on the local machine.

Create a folder named `build`, and then generate the makefile with CMake:

`cmake -S source/ -B build/ -D PYTHON_INCLUDE=../include/pythonXY -D PYTHON_VERSION=pythonXY`

The flags `PYTHON_INCLUDE` and `PYTHON_VERSION` are required to include the [matplotlib](https://matplotlib-cpp.readthedocs.io/en/latest/) porting in C++.

Then compile with inside the `build` folder with:

`cd build`

`make`

## Usage
The folder containing the plots with the results are saved one level up with respect the main folder of the project `scicomp`. The folder structure should be: `build`, `scicomp`, and `plots`. The `plots` folder is created the first time an operation which requires to plot a graph is called. The location of `plots` is one upper level with respect the folder where there is the executable, which by default is `build`.

### Lotka-Volterra Model
The [Lotka-Volterra](https://en.wikipedia.org/wiki/Lotka%E2%80%93Volterra_equations) model describes how the population of two species change when they interact. This model is also known as predator-prey model. 

The Lotka-Volterra model is described by the following pair of equations:

$\frac{dx}{dt}$ = $ax - bxy$

$\frac{dy}{dt}$ = $cxy - dy$,


where we have:
- $a$: grow of the preys
- $b$: interaction term between prey and predator
- $c$: grow of the predators
- $d$: death rate of the predators

We then have that the required parameters to solve these equations are:
- n: number of step
- dt: time step
- x_0: initial number of prey
- y_0: initial number of predator
- a: grow of the prey
- b: interaction term between prey and predator
- c: grow of the predator
- d: death rate of the predator

Example: `./scicomp lv n=10000 dt=0.01 x_0=2 y_0=1 a=0.7 b=0.5 c=0.3 d=0.2`.