#define _CRT_SECURE_NO_WARNINGS  // Disable CRT warnings for learning purposes
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "circuit_solver.h"  // Your header with function prototypes

#define MAX_RESISTORS 100  // Maximum allowed resistors



int main() {
    int num_resistors;
    char solve_type[10];  // String buffer for "series" or "parallel"

    // Input number of resistors
    printf("Enter Number Of Resistors (max %d): ", MAX_RESISTORS);
    scanf_s("%d", &num_resistors);

    // Validate number of resistors
    if (num_resistors <= 0 || num_resistors > MAX_RESISTORS) {
        printf("Invalid number of resistors.\n");
        return 1;
    }

    int resistor_value[MAX_RESISTORS];  // Fixed-size array

    // Input resistor values
    for (int i = 0; i < num_resistors; i++) {
        printf("Enter Resistor Value (Ohms) for resistor %d: ", i + 1);
        scanf_s("%d", &resistor_value[i]);
    }

    // Input series or parallel calculation choice
    printf("Solve in series or parallel? (type 'series' or 'parallel'): ");
    scanf_s("%9s", solve_type, 10);  // Safe input, max 9 chars + null terminator

    // Compare input and calculate accordingly
    if (strcmp(solve_type, "series") == 0) {
        int series_value = series_solver(resistor_value, num_resistors);
        printf("The Total Resistance in series is %d ohms\n", series_value);
    }
    else if (strcmp(solve_type, "parallel") == 0) {
        double parallel_value = parallel_solver(resistor_value, num_resistors);
        printf("The Total Resistance in parallel is %.2f ohms\n", parallel_value);
    }
    else {
        printf("Invalid input. Please type 'series' or 'parallel'.\n");
        return 1;
    }

    return 0;
}

// Function to calculate total series resistance
int series_solver(int resistor_value[], int num_resistors) {
    int series_value = 0;
    for (int i = 0; i < num_resistors; i++) {
        series_value += resistor_value[i];
    }
    return series_value;
}

// Function to calculate total parallel resistance
double parallel_solver(int resistor_value[], int num_resistors) {
    double reciprocal_sum = 0.0;

    for (int i = 0; i < num_resistors; i++) {
        if (resistor_value[i] == 0) {  // Avoid division by zero
            printf("Error: Resistor value cannot be zero in parallel.\n");
            return 0.0;
        }
        reciprocal_sum += 1.0 / resistor_value[i];  // Ensure double division
    }

    return 1.0 / reciprocal_sum;
}
