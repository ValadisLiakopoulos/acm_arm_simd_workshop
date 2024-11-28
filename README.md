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

Each of these functions is optimized with ARM's NEON SIMD instructions. The time taken for all calculations is measured using `clock()`, and the total execution time for the entire program is displayed.

```c
clock_t start_time = clock();
clock_t end_time = clock();
double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
printf("Total time taken for calculations: %.6f seconds\n", time_taken);
```

This allows for a precise measurement of the time taken for each SIMD-optimized operation, enabling you to compare performance gains when using SIMD.
