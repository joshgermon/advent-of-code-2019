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

    if(code == 1) {
        array[index_of_result] = array[first_num] + array[second_num];
    }
    if(code == 2) {
        array[index_of_result] = array[first_num] * array[second_num];
    }
    if(code == 99) {
        return 1;
    }
    return 0;
}


int main(int argc, char* argv[]) {
    printf("****ADVENT OF CODE 2019 - DAY TWO ****\n");

    char *input = read_input_file();
    int target_output = 19690720;

    // Split input string, convert to int and add to array
    const char *delim = ",";
    char *current_num = strtok(input, delim);

    // Hardcoding array size, no need to realloc for this fixed input
    // but could've been good practice
    int input_numbers[153];
    int idx = 0;

    while(current_num) {
        input_numbers[idx] = atoi(current_num);
        current_num = strtok(NULL, delim);
        idx++;
    }

    // Yeah, look not perfect solution but my frustration trying to understand wtf part 2
    // was asking led to this solution and not wanting to spend any time making it better
    int p1, p2;
    for(p1 = 0; p1 <= 100; p1++) {
        for(p2 = 0; p2 <= 100; p2++) {
            // Reset the memory to its initial state for each iteration
            int input_numbers_copy[153];
            memcpy(input_numbers_copy, input_numbers, sizeof(input_numbers));

            input_numbers_copy[1] = p1;
            input_numbers_copy[2] = p2;

            int intcode_idx = 0;
            while(intcode_idx < 153) {
                int result = process_intcode(intcode_idx, input_numbers_copy);
                if(result == 1) {
                    break;
                }
                intcode_idx += 4;
            }

            if(input_numbers_copy[0] == target_output) {
                int output = 100 * p1 + p2;
                printf("Found target pair: 100 * %d + %d = %d", p1, p2, output);
                break;
            }
        }
    }

    return 0;
}


