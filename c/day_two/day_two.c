#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILENAME "input.txt"

char *read_input_file() {
    FILE* fptr = fopen(INPUT_FILENAME, "r");

    if (fptr == NULL) {
        printf("Error: File not found");
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    int length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char *string = malloc(sizeof(char) * (length+1));

    char c;
    int i = 0;

    while((c = fgetc(fptr)) != EOF) {
        string[i] = c;
        i++;
    }

    string[i] = '\0';
    fclose(fptr);
    return string;
}

int process_intcode(int pos, int array[]) {
    int code = array[pos];
    int first_num = array[pos+1];
    int second_num = array[pos+2];
    int index_of_result = array[pos+3];

    printf("Program code: %d\n", code);

    if(code == 1) {
        printf("Program code: Addition\n");
        printf("Processing: %d + %d in position %d\n", array[first_num], array[second_num], array[index_of_result]);
        array[index_of_result] = array[first_num] + array[second_num];
    }
    if(code == 2) {
        printf("Program code: Multiplication\n");
        printf("Processing: %d * %d in position %d\n", array[first_num], array[second_num], array[index_of_result]);
        array[index_of_result] = array[first_num] * array[second_num];
    }
    if(code == 99) {
        printf("Program code: HALT\n");
        return 1;
    }
    return 0;
}


int main(int argc, char* argv[]) {
    printf("****ADVENT OF CODE 2019 - DAY TWO ****\n");

    char *input = read_input_file();

    // Split input string, convert to int and add to array
    const char *delim = ",";
    char *current_num = strtok(input, delim);

    // There's possibly a better way to allocate this array size
    int input_numbers[153];
    int idx = 0;

    while(current_num) {
        input_numbers[idx] = atoi(current_num);
        current_num = strtok(NULL, delim);
        idx++;
    }

    // Restore 1202 program alarm
    input_numbers[1] = 12;
    input_numbers[2] = 2;

    int intcode_idx = 0;
    while(intcode_idx < 153) {
        printf("idx loop: %d, array intcode val: %d\n", intcode_idx, input_numbers[intcode_idx]);
        int result = process_intcode(intcode_idx, input_numbers);
        if(result == 1) {
            break;
        }
        intcode_idx += 4;
    }

    printf("Position 0 is: %d\n", input_numbers[0]);

    return 0;
}


