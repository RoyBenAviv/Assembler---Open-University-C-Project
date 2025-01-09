#include "data.h"

int main(int argc, char *argv[]) {
    char** memory;
    LinkedList* symbols_list;
    FILE* file_after_macro;
    char buffer[LINE_LENGTH];
	char* file_name;
    int current_address_value;
    int instruction_counter;
    int data_counter;
    int file_name_length;
    int i;
	int marco_success_code;

	if(argc == 1){
        printf("Error: No files selected.\n");
        exit(1);
    }
    
    while(argc > 1) {
	
	file_name = argv[argc - 1];
    file_name_length = strlen(file_name);
	
    printf("File being processed: %s\n", file_name);

	marco_success_code = proccess_macro_file(file_name);

	if(marco_success_code != 0) {
		printf("Failed to proccess macro\n");
		exit(1);
	}

	(file_name)[file_name_length] = '\0';

    memory = (char**)malloc(MEMORY_LENGTH * sizeof(char*)); /* Allocate Memory */
    if (memory == NULL) {
        printf("Memory allocation for memory failed\n");
        exit(1);
    }

    symbols_list = (LinkedList*)malloc(sizeof(LinkedList)); /* Allocate Symbol list */
    if (symbols_list == NULL) {
        printf("Memory allocation for symbol list failed\n");
        exit(1);
    }

    symbols_list->head = NULL; /* Initialize Symbol List */


    for (i = MEMORY_START; i < MEMORY_LENGTH; i++) { /* Initialize Memory */
        memory[i] = NULL;
    }


	(file_name)[file_name_length] = '\0';
	file_after_macro = fopen(strcat(file_name, ".as"), "r");

    if (file_after_macro == NULL) {
        printf("Error opening file\n");
        argc--;
		continue;
    }


    current_address_value = MEMORY_START;
    instruction_counter = 0;
    data_counter = 0;
    while (fgets(buffer, sizeof(buffer), file_after_macro) != NULL) {
        trim(buffer);

        if (is_line_empty_or_comment(buffer)) continue;

        if (current_address_value >= MEMORY_LENGTH) {
            printf("No more space on memory! \n"); 
            exit(1);
        }


        process_first_pass(buffer, &instruction_counter, &data_counter, &current_address_value, symbols_list, memory);
    }   

    rewind(file_after_macro); /* Reset file Macro */

    current_address_value = MEMORY_START; /* Reset the address value */

    while (fgets(buffer, sizeof(buffer), file_after_macro) != NULL) {

        trim(buffer);

        if (is_line_empty_or_comment(buffer)) continue;

        process_second_pass(buffer, &current_address_value, symbols_list, memory);

    }
	

    (file_name)[file_name_length] = '\0';
    print_memory_to_file(MEMORY_LENGTH, memory, data_counter, instruction_counter, file_name);

    (file_name)[file_name_length] = '\0';
    print_symbol_list_to_file(symbols_list, file_name, file_name_length);
    free(symbols_list);
    free(memory);
	

	argc--;
	}


    return 0;
}
