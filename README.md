# Scientific Computing

In this personal project I implement in C++ the numerical solution of some famous mathematical models.

The models implemented are:

- The [Lotka-Volterra](https://en.wikipedia.org/wiki/Lotka%E2%80%93Volterra_equations) model solved by using the Runge-Kutta method ([RK4](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods)).
- The [Navier-Stokes](https://en.wikipedia.org/wiki/Navier%E2%80%93Stokes_equations) equations solved with the [finite volume method](https://en.wikipedia.org/wiki/Finite_volume_method) for the lid driven cavity flow problem.

## Compilation

To compile `scicomp` the C++ version must be greater than 17.
CMake is used to create the makefile. 

The only dependency is the [Matplot++](https://alandefreitas.github.io/matplotplusplus/) library downloaded automatically while generating the makefile.

Create a folder named `build`, and then generate the makefile with CMake:

`cmake -S source/ -B build/`

Hence, compile inside the `build` folder with:

`cd build`

`make`

## Usage
### Lotka-Volterra Model

The [Lotka-Volterra](https://en.wikipedia.org/wiki/Lotka%E2%80%93Volterra_equations) model describes how the population of two species changes when they interact. This model is also known as predator-prey model. 

The required parameters to solve these equations are:

- n: number of step
- dt: time step
- x_0: initial number of prey
- y_0: initial number of predator
- a: grow rate of the prey
- b: interaction term between prey and predator
- c: grow rate of the predator
- d: death rate of the predator

This system of ordinary differential equations is numerically solved by using the 
classical Runge-Kutta method (RK4).

Example: `./scicomp lv n=10000 dt=0.01 x_0=2 y_0=1 a=0.7 b=0.5 c=0.3 d=0.2`.

The results are saved one level up with respect the location of the executable file in a folder named `plots`.

### 2D Navier-Stokes Equation

The [Navier-Stokes](https://en.wikipedia.org/wiki/Navier%E2%80%93Stokes_equations) equations are partial
differential equations that describe the motion of viscous fluids. In this case we will focus on incompressible fluids and for the  two dimensional case. These equations are solved numerically by using the [finite volume method](https://en.wikipedia.org/wiki/Finite_volume_method) for the lid driven cavity flow problem by following the lecture series of [Coding for Lid Driven Cavity Flow Simulation in C](https://www.youtube.com/watch?v=_yL5zd_-rBI).

The required parameters are:
- nx: size along the x direction
- ny: size along the y direction
- dt: time step
- re: Reynolds number
- rho: density
- nu: kinematic viscosity

Example: `./scicomp ns cavity2d nx=41 ny=41 dt=0.001 re=100 rho=0.1 nu=0.01`.

The results are saved one level up with respect the location of the executable file in a folder named `ns_res`. The components of the velocity and the pressure are saved in three different files named: `u_out.txt`, `v_out.txt`, and `p_out.txt` respectively. These files can be later plotted, for example, by using [Matplotlib](https://matplotlib.org/).