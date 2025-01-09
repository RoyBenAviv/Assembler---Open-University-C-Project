#include "data.h"

void process_first_pass(char* buffer, int* instruction_counter, int* data_counter, int* current_address_value, LinkedList* symbols_list, char** memory) {

    char first_str_part[LINE_LENGTH];
    char* remaining_buffer;
    int first_str_part_length;
    int address;

    remaining_buffer  = extract_first_word(buffer, first_str_part);
    trim(remaining_buffer);

    first_str_part_length = strlen(first_str_part);
    if (is_symbol(first_str_part)) { /* Symbol found */
        first_str_part[first_str_part_length - 1] = '\0';
        if (!is_string_exists(symbols_list, first_str_part)) { /* Checks if the symbol can be added to the symbol list */
            char second_str_part[LINE_LENGTH];
            remaining_buffer = extract_first_word(remaining_buffer, second_str_part);
            trim(remaining_buffer);
            add_symbol(symbols_list, first_str_part, current_address_value, second_str_part); /* add symbol to symbol list */
            if (strcmp(second_str_part, ".string") == 0) { /* In case .string -> convert string to ascii binary  */
                convert_string_to_ascii(remaining_buffer, data_counter, current_address_value, memory);
            }
            else if (strcmp(second_str_part, ".data") == 0) { /* In case .data -> convert number to ascii binary  */
                convert_number_to_ascii(remaining_buffer, data_counter, current_address_value, memory);
            }
            else {
                char* second_str_part;
                second_str_part = buffer + first_str_part_length;
                trim(second_str_part);
                process_command_first_pass(second_str_part, instruction_counter, current_address_value, symbols_list, memory); /* process the command */
            }
        } else {
            printf("Symbol cannot entered to the symbols list\n");
        }
    }
    else {
        if (strcmp(first_str_part, ".string") == 0) {
            convert_string_to_ascii(remaining_buffer, data_counter, current_address_value, memory); /* In case .string -> convert string to ascii binary  */
        } else if (strcmp(first_str_part, ".data") == 0) {
            convert_number_to_ascii(remaining_buffer, data_counter, current_address_value, memory); /* In case .data -> convert number to ascii binary  */
        }
        else if (strcmp(first_str_part, ".extern") == 0) {
            address = 0;
            add_symbol(symbols_list, remaining_buffer, &address, first_str_part); /* add symbol to symbol list */
        }
 		else {
            process_command_first_pass(buffer, instruction_counter, current_address_value, symbols_list, memory); /* process the command */
        }
    }
}
