# SIMD Operations with NEON on Raspberry Pi Zero 2 W

This repository contains a series of functions to demonstrate the use of ARM's NEON SIMD instructions for efficiently processing data from a CSV file. The functions include calculations such as averages, vector magnitudes, least-squares fit, and variance.

## Functions

### 1. **Average of x-axis (g), y-axis (g), and z-axis (g)**
   
**Math:**
\[
\text{Average} = \frac{1}{n} \sum_{i=1}^{n} x_i
\]
Where \(x_i\) are the elements of the array and \(n\) is the number of elements.

**Description:**
This function calculates the average of an array of floats (e.g., acceleration values in g). It uses SIMD to process multiple elements at once for efficiency.

**Function:**
```c
float calculate_average_neon(float *data, int n);
```

### 2. **Vector Magnitudes of the Acceleration Vector**

**Math:**
\[
\text{Magnitude} = \sqrt{x^2 + y^2 + z^2}
\]
Where \(x\), \(y\), and \(z\) are the components of the vector.

**Description:** 
This function calculates the magnitude of a 3D vector (e.g., acceleration vector composed of x-axis, y-axis, and z-axis values) for each data point. It uses NEON SIMD instructions to calculate the magnitudes for multiple points at once.

**Function:**
```c
void calculate_magnitudes_neon(float *x, float *y, float *z, float *magnitudes, int n);
```

### 3. **Least-Squares Fit (Linear Regression)**

**Math:**
\[
m = \frac{n\sum xy - \sum x \sum y}{n \sum x^2 - (\sum x)^2}
\]
\[
b = \frac{\sum y - m \sum x}{n}
\]
Where \(m\) is the slope, \(b\) is the intercept, \(x\) is the independent variable, and \(y\) is the dependent variable.

**Description:** 
This function calculates the slope and intercept of a linear regression line using the least-squares method. The result is a linear model of the form \(y = mx + b\). NEON SIMD is used to perform the summations and calculations in parallel for faster performance.

**Function:**
```c
void calculate_least_squares_neon(float *x, float *y, int n, float *m, float *b);
```

### 4. **Variance of z-axis (g) Values**

**Math:**
\[
\text{Variance} = \frac{1}{n} \sum_{i=1}^{n} (x_i - \mu)^2
\]
Where \(x_i\) are the elements of the array and \(\mu\) is the mean of the array.

**Description:** 
This function calculates the variance of the data points in the array (e.g., z-axis acceleration in g). It computes how spread out the values are from the mean. SIMD operations are used to calculate the squared differences from the mean for all values at once.

**Function:**
```c
float calculate_variance_neon(float *data, int n);
```

## Timing

The time taken for all calculations is measured using a struct `get_wtime` that exists in the code.

```c
double get_wtime(void){
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec*1.0e-6;
}
```

This allows for a precise measurement of the time taken for each SIMD-optimized operation, enabling you to compare performance gains when using SIMD.

# Working on the Project

Make sure you only write code on the file `main-program-simd.c`. ***DO NOT*** change the scalar one. You need it to check the validity of your results in the SIMD version.

## SSH Connection to your Raspberry Pi Zero 2W

Workshop supervisor will give you a raspberry pi and an IP Address to connect via Secure Shell. In order to establish an SSH connection, run on your terminal:

```shell
ssh user@192.168.1.X
```
Credentials are `user` and password `user`. The X value is dependent on the raspberry that will be assigned to your team.

## Where to find help for SIMD

1. Official Arm [Documentation](https://developer.arm.com/architectures/instruction-sets/intrinsics/) 
2. Of course, [SIMD.info](https://simd.info)
3. AI is your friend. You can use the chatbot of your liking.

## Compilation of code

In order for a C program to run, the source code needs to be compiled with linked libraries. In order to make the compilation stage easier for the contenstant, we'll use `Makefile`.

### Compile for the first time

If you going to compile the code for the first time, make sure you are in the directory that contains the `Makefile`. Then run on your terminal:
```shell
make
```
You should see the code getting compiled.

### Compiling after the first time

If you are going to compile again, make sure to remove all executables that are already created.
To do that, run on your terminal:
```shell
make clean
```

It will remove all binaries from the code folder.

### Compile one file only

In order to compile one file only, run on your terminal:
```shell
make scalar
```
To compile only the serial version or:
```shell
make simd
```
To compile the SIMD version of the code.

## Executing the C programs

At last, you have to run the serial program and your SIMD solution. Run on your terminal:

```shell
./scalar_program
```
For the scalar/serial program, and:

```shell
./simd_program
```
For the SIMD program that you wrote.

In the terminal, you should see the results and the time taken for execution.

# Contest

In order to win the prizes as a team, you'll be judged based on the solution you will give. Some of the criteria are:

- The code execution is flawless
- The good use of SIMD Instructions
- The time difference of the scalar and SIMD solution
- The absence of warnings in the compilation phase

