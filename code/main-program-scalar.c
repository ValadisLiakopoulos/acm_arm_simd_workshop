#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arm_neon.h>
#include <math.h>

#define MAX_LINE_LENGTH 256
#define MAX_LINES 33000

// average of an array of floats
float calculate_average_scalar(float *data, int n) {

    /* 
        Math type: Average = (1/n)*sum(vector) 
    */

    float sum = 0.0f;

    // sequentially add all elements
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }

    // calculate average
    return sum / n;
}

// calculate vector magnitudes
void calculate_magnitudes_scalar(float *x, float *y, float *z, float *magnitudes, int n) {

    /* 
        This function computes the magnitudes of 3D vectors using their x, y, z components.
        The magnitude of a vector is a measure of its length in 3D space.

        The magnitude of a vector v = (x, y, z) is given by:

                |v| = sqrt(x^2 + y^2 + z^2)
    */

    for (int i = 0; i < n; i++) {
        magnitudes[i] = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
    }
}

// calculate least squares fit (linear regression)  
void calculate_least_squares_scalar(float *x, float *y, int n, float *m, float *b) {
    
    /* 
        This function computes the linear regression parameters m-slope and b (y-intercept)
        for a given set of data points (x, y). The linear regression model fits a straight 
        line to the data, minimizing the squared differences between the observed y-values 
        and the predicted y-values from the model.

        The slope m and intercept b of the line are given by:

            m = (n*sum(x*y) - sum(x)*sum(y)) / (n*sum(x^2) - sum(x)^2)
            b = sum(y)/n - m*sum(x)/n
    */

    float x_sum = 0.0f, y_sum = 0.0f, xy_sum = 0.0f, x2_sum = 0.0f;

    // sequentially compute summations
    for (int i = 0; i < n; i++) {
        x_sum += x[i];
        y_sum += y[i];
        xy_sum += x[i] * y[i];
        x2_sum += x[i] * x[i];
    }

    // compute means
    float x_mean = x_sum / n;
    float y_mean = y_sum / n;

    // compute slope and intercept
    *m = (xy_sum - n * x_mean * y_mean) / (x2_sum - n * x_mean * x_mean);
    *b = y_mean - (*m) * x_mean;
}

// calculate variance
float calculate_variance_scalar(float *data, int n) {
    
    /*
        This function computes the variance of an array of data points. 
        Variance is a measure of how spread out the values are around the mean. 
        
        The formula for variance is:
            
            Variance = (1/n) * sum((x_i - mean)^2)
    */
   
   float mean = 0.0f;
    float variance = 0.0f;

    // Calculate mean
    for (int i = 0; i < n; i++) {
        mean += data[i];
    }
    mean /= n;

    // Calculate variance
    for (int i = 0; i < n; i++) {
        float diff = data[i] - mean;
        variance += diff * diff;
    }

    return variance / n;
}


int main() {
    // file pointer and line buffer
    FILE *file = fopen("data.csv", "r");
    if (!file) {
        perror("Unable to open file");
        return EXIT_FAILURE;
    }

    // arrays to store data
    // each array contains the corresponding data for each collumn (x_g, y_g, z_g, x_deg, y_deg, z_deg)
    int line_id[MAX_LINES];
    float x_g[MAX_LINES], y_g[MAX_LINES], z_g[MAX_LINES];
    float x_deg[MAX_LINES], y_deg[MAX_LINES], z_deg[MAX_LINES];

    // skip header
    char buffer[MAX_LINE_LENGTH];
    if (fgets(buffer, MAX_LINE_LENGTH, file) == NULL) {
        perror("Error reading header");
        fclose(file);
        return EXIT_FAILURE;
    }

    // read file line by line
    int count = 0;
    while (fgets(buffer, MAX_LINE_LENGTH, file) && count < MAX_LINES) {
        // parse values from the line
        if (sscanf(buffer, "%d,%f,%f,%f,%f,%f,%f",
                   &line_id[count], &x_g[count], &y_g[count], &z_g[count],
                   &x_deg[count], &y_deg[count], &z_deg[count]) != 7) {
            fprintf(stderr, "Error parsing line %d: %s", count + 1, buffer);
            continue;
        }
        count++;
    }

    fclose(file);
    
    // output data to verify
    // printf("Read %d lines from data.csv:\n", count);
    // for (int i = 0; i < count; i++) {
    //     printf("Line %d: %f, %f, %f, %f, %f, %f\n",
    //            line_id[i], x_g[i], y_g[i], z_g[i], x_deg[i], y_deg[i], z_deg[i]);
    // }
    

    // ------------------------- CALCULATION FUNCTIONS ------------------------------
    // average of x_g, y_g, z_g
    printf("Calculating averages...\n");
    printf("Average x_g: %f\n", calculate_average_scalar(x_g, count));
    printf("Average y_g: %f\n", calculate_average_scalar(y_g, count));
    printf("Average z_g: %f\n", calculate_average_scalar(z_g, count));

    // vector magnitudes of x_g, y_g, z_g
    printf("\nCalculating vector magnitudes...\n");
    float magnitudes[MAX_LINES];
    calculate_magnitudes_scalar(x_g, y_g, z_g, magnitudes, count);
    printf("First 5 magnitudes: ");
    for (int i = 0; i < 5 && i < count; i++) {
        printf("%f ", magnitudes[i]);
    }
    printf("\n");

    // least-squares fit (linear regression) of x_deg, y_deg
    printf("\nCalculating least-squares fit (linear regression)...\n");
    float m, b;
    calculate_least_squares_scalar(x_deg, y_deg, count, &m, &b);
    printf("Slope (m): %f\n", m);
    printf("Intercept (b): %f\n", b);

    // variance of z_g
    printf("\nCalculating variance of z_g...\n");
    printf("Variance of z_g: %f\n", calculate_variance_scalar(z_g, count));

    return EXIT_SUCCESS;
}
