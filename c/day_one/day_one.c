#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILENAME "input.txt"

int calculate_fuel_from_mass() {
    FILE* fptr;

    fptr = fopen(INPUT_FILENAME, "r");
    char line[256];

    if (fptr == NULL) {
        printf("Error: File not found");
        return 1;
    }

    printf("Calulating fuel requirements\n");

    int sum_of_fuel_needed = 0;

    while(fgets(line, sizeof(line), fptr)) {
        // Read in line and convert to an integer
        int module_mass = atoi(line);

        // Calculate intial fuel needed for module mass
        int calculated_fuel = module_mass / 3 - 2;

        // Calculate the additional fuel needed for the module required fuel
        while(calculated_fuel > 0) {
            sum_of_fuel_needed += calculated_fuel;
            calculated_fuel = calculated_fuel / 3 - 2;
        }
        // Progress bar
        printf(".");
    }

    fclose(fptr);

    printf("\nCalculations completed. ✔\n");
    return sum_of_fuel_needed;
}

int main(int argc, char* argv[]) {
    printf("****ADVENT OF CODE 2019 - DAY ONE ****\n");

    int fuel_needed = calculate_fuel_from_mass();

    printf("Fuel required: %i\n", fuel_needed);

    return 0;
}

