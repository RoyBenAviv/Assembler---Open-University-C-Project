#include "data.h"

void process_second_pass(char* buffer, int *current_address_value, LinkedList* symbols_list, char** memory) {

    

    char first_str_part[LINE_LENGTH];
    char* remaining_buffer;
    int first_str_part_length;

    remaining_buffer = extract_first_word(buffer, first_str_part);
    trim(remaining_buffer);
    
    first_str_part_length = strlen(first_str_part);
    if (is_symbol(first_str_part)) { /* Symbol found */
        char second_str_part[LINE_LENGTH];
        remaining_buffer = extract_first_word(remaining_buffer, second_str_part);
        trim(remaining_buffer);
        if (strcmp(second_str_part, ".string") != 0 && strcmp(second_str_part, ".data") != 0) {
            char* second_str_part;
            second_str_part = buffer + first_str_part_length;
            trim(second_str_part);
            process_command_second_pass(second_str_part, current_address_value, symbols_list, memory); /* process the command to find symbols */
        }
    } else {
        trim(first_str_part);
        if (strcmp(first_str_part, ".extern") == 0 || strcmp(first_str_part, ".entry") == 0) {
            update_symbol_instruction(symbols_list, remaining_buffer, first_str_part); /* update extern and entry instructions to the symbol list */
        }
        else if (strcmp(first_str_part, ".string") != 0 && strcmp(first_str_part, ".data") != 0) {
           process_command_second_pass(buffer, current_address_value, symbols_list, memory); /* process the command to find symbols */
        }

    }
    
}


