#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    printf("****ADVENT OF CODE 2019 - DAY ONE ****\n");
    printf("Calulating fuel requirements...\n");

    FILE* fptr;

    fptr = fopen("input.txt", "r");
    char line[256];

    if (fptr == NULL) {
        printf("Error: File not found");
        return 1;
    }

    int sum_of_fuel_needed = 0;

    while(fgets(line, sizeof(line), fptr)) {
        int calculated_fuel = (atoi(line) / 3) - 2;
        sum_of_fuel_needed += calculated_fuel;
    }

    fclose(fptr);

    printf("Calculations completed.\nFuel required: %i\n", sum_of_fuel_needed);
}
