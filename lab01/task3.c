#include <stdio.h>

/*
 * Lab 1, Task 3, Variant 4: energy and charge of a charged capacitor.
 * Formulas: W = C * U^2 / 2,  q = C * U
 */
int main(void) {
    const double energy_divisor = 2.0;  // divisor in W = C * U^2 / 2

    double capacitance = 0.0;  // C, farads
    double voltage = 0.0;      // U, volts

    printf("Enter capacitance C (F), e.g. 100e-6: ");
    if (scanf("%lf", &capacitance) != 1) {
        printf("Error: capacitance must be a number.\n");
        return 1;
    }

    // Capacitance is a physical quantity and must be strictly positive
    if (capacitance <= 0.0) {
        printf("Error: capacitance must be greater than zero.\n");
        return 1;
    }

    printf("Enter voltage U (V): ");
    if (scanf("%lf", &voltage) != 1) {
        printf("Error: voltage must be a number.\n");
        return 1;
    }

    double energy = capacitance * voltage * voltage / energy_divisor;
    double charge = capacitance * voltage;

    printf("Stored energy W = %.3e J\n", energy);
    printf("Charge        q = %.3e C\n", charge);

    return 0;
}