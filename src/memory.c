#include "data.h"


void add_to_memory(int * current_address_value, int* counter, char* bits, char** memory) {
    memory[*current_address_value] = bits;
    (*current_address_value)++;
    if ((*counter) != -1) (*counter)++;
}

void print_memory_to_file(int size, char** memory, int data_counter, int instruction_counter, char* file_name) {
    int i;
    FILE* file;
    char* octal_number;
        
    file = fopen(strcat(file_name, ".ob"), "w");

    if (file == NULL) {
        printf("Failed to open file");
        return;
    }

    fprintf(file, "   %d\t%d\n", instruction_counter, data_counter);
    
    i = MEMORY_START;
    while (memory[i] != NULL && i < size) {

       octal_number = binary_to_octal(memory[i]);
       fprintf(file, "%d \t %s\n", i, octal_number);
       i++;
    }


    fclose(file);

    printf("Data written to ps.ob successfully.\n");

}
