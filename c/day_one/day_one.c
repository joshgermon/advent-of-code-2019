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

    int sum_of_fuel_needed = 0;

    while(fgets(line, sizeof(line), fptr)) {
        // Calculate fuel needed from module mass
        int calculated_module_fuel = (atoi(line) / 3) - 2;
        sum_of_fuel_needed += calculated_module_fuel;

        // Calculate fuel needed for fuel required by module mass
        int calculated_fuel_fuel = calculated_module_fuel / 3 - 2;

        while(calculated_fuel_fuel > 0) {
            sum_of_fuel_needed += calculated_fuel_fuel;
            calculated_fuel_fuel = calculated_fuel_fuel / 3 - 2;
        }
    }

    fclose(fptr);
    return sum_of_fuel_needed;
}

int main(int argc, char* argv[]) {

    printf("****ADVENT OF CODE 2019 - DAY ONE ****\n");
    printf("Calulating fuel requirements...\n");

    // Part one calculation method
    int fuel_needed = calculate_fuel_from_mass();

    printf("Calculations completed.\nFuel required: %i\n", fuel_needed);

    return 0;
}

