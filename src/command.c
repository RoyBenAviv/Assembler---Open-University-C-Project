#include "data.h"

void handle_group1(int* current_address_value, int* instruction_counter, char* first_word, char* first_external_word, char* second_external_word, char* combined_external_word, int first_operand_method, int second_operand_method, int opcode_idx, char* first_operand, char* second_operand, char** memory, LinkedList* symbols_list) {
    handle_first_word(&first_word, first_operand_method, second_operand_method, opcode_idx);
    add_to_memory(current_address_value, instruction_counter, first_word, memory);

    if ((first_operand_method == 2 && second_operand_method == 2) ||
        (first_operand_method == 3 && second_operand_method == 3) ||
        (first_operand_method == 2 && second_operand_method == 3) ||
        (first_operand_method == 3 && second_operand_method == 2)) {
	/* Handle combined external word */
        handle_combined_external_word(&combined_external_word, first_operand_method, second_operand_method, first_operand, second_operand);
        add_to_memory(current_address_value, instruction_counter, combined_external_word, memory);
    }
    else {
	/* Handle external words */
        handle_external_words(&first_external_word, &second_external_word, first_operand_method, second_operand_method, first_operand, second_operand, symbols_list);
        add_to_memory(current_address_value, instruction_counter, first_external_word, memory);
        add_to_memory(current_address_value, instruction_counter, second_external_word, memory);
    }
}

void handle_group2(int* current_address_value, int* instruction_counter, char* first_word, char* first_external_word,char* second_external_word, int first_operand_method, int opcode_idx, char* first_operand, char** memory, LinkedList* symbols_list) {
    handle_first_word(&first_word, -1, first_operand_method, opcode_idx);
    handle_external_words(&first_external_word, &second_external_word, -1, first_operand_method, first_operand, first_operand, symbols_list);
    add_to_memory(current_address_value, instruction_counter, first_word, memory);
    add_to_memory(current_address_value, instruction_counter, second_external_word, memory);
}

void handle_group3(int* current_address_value, int* instruction_counter, char* first_word, int opcode_idx, char** memory) {
    handle_first_word(&first_word, -1, -1, opcode_idx);
    add_to_memory(current_address_value, instruction_counter, first_word, memory);
}

int process_command_first_pass(char* str, int* instruction_counter, int* current_address_value, LinkedList* symbols_list, char** memory) {

    Opcode opcodes[OPCODES_LENGTH];
    Opcode current_opcode;
    char* command_name;
    int first_operand_method;
    int second_operand_method;
    char* first_word;
    char* first_external_word;
    char* second_external_word;
    char* combined_external_word;
    char* first_operand;
    char* second_operand;
    int opcode_idx;

	
    initialize_opcodes(opcodes);
    initialize_words(&first_word, &first_external_word, &second_external_word, &combined_external_word);

    first_operand_method = -1;
    second_operand_method = -1;

    command_name = concat_str(str, " "); /* take only the command name from the str (first word) */


    if (command_name == NULL) {
        return 0;
    }
    opcode_idx = find_opcode_idx(command_name, opcodes);
    if (opcode_idx == -1) {
        printf("Invalid opcode: %s\n", command_name);
        return 0;
    }
    current_opcode = opcodes[opcode_idx];

    parse_operands(str, &first_operand, &second_operand);

    first_operand_method = find_addressing_method(first_operand, symbols_list);
    second_operand_method = find_addressing_method(second_operand, symbols_list);
        

    if (!check_operands(current_opcode, first_operand_method, second_operand_method)) {
        return 0;
    }

    switch (current_opcode.group_number) {
    case 1:
        handle_group1(current_address_value, instruction_counter, first_word, first_external_word, second_external_word,
            combined_external_word, first_operand_method, second_operand_method,
            opcode_idx, first_operand, second_operand, memory, symbols_list);
        break;
    case 2:
        handle_group2(current_address_value, instruction_counter, first_word, first_external_word, second_external_word,
            first_operand_method, opcode_idx, first_operand, memory, symbols_list);
        break;
    case 3:
        handle_group3(current_address_value, instruction_counter, first_word, opcode_idx, memory);
        break;
    }

    return 1;
}


int process_command_second_pass(char* str, int* current_address_value, LinkedList* symbols_list, char** memory) {

	

    Opcode opcodes[OPCODES_LENGTH];
    Opcode current_opcode;
    char* command_name;
    int first_operand_method;
    int second_operand_method;
    int opcode_idx;
    int counter;
    char* first_operand;
    char* second_operand;
    char* symbol_word;

    first_operand_method = -1;
    second_operand_method = -1;
    initialize_opcodes(opcodes);
	
    command_name = concat_str(str, " "); /* take only the command name from the str (first word) */


    trim(command_name);
    if (command_name == NULL) {
        return 0;
    }
    opcode_idx = find_opcode_idx(command_name, opcodes);
    if (opcode_idx == -1) {
        return 0;
    }
    current_opcode = opcodes[opcode_idx];

    parse_operands(str, &first_operand, &second_operand);

    first_operand_method = find_addressing_method(first_operand, symbols_list);
    second_operand_method = find_addressing_method(second_operand, symbols_list);

    if (first_operand_method == -2) {
	printf("Error on finding word: %s\n", first_operand);
	(*current_address_value)++;
        return 0;
    }

    if (second_operand_method == -2) {
	printf("Error on finding word: %s\n", second_operand);
	(*current_address_value)++;
        return 0;
    }


    (*current_address_value)++;

    
    counter = -1;
    switch (current_opcode.group_number) {
    case 1:
    {

        if ((first_operand_method == 2 && second_operand_method == 2) ||
            (first_operand_method == 3 && second_operand_method == 3) ||
            (first_operand_method == 2 && second_operand_method == 3) ||
            (first_operand_method == 3 && second_operand_method == 2)) {
            (*current_address_value)++; 
        }
        else {

            if (first_operand_method == 1) {
                symbol_word = NULL;
                symbol_word = get_symbol_word(first_operand, symbols_list, current_address_value);
                add_to_memory(current_address_value, &counter, symbol_word, memory);
            }
            else {
                (*current_address_value)++;
            }

            if (second_operand_method == 1) {
                symbol_word = NULL;
                symbol_word = get_symbol_word(second_operand, symbols_list, current_address_value);
                add_to_memory(current_address_value, &counter, symbol_word, memory);
            }
            else {
                (*current_address_value)++;
            }
        }
    }

    break;
    case 2:
    {

        if (first_operand_method == 1) {
            symbol_word = NULL;
            symbol_word = get_symbol_word(first_operand, symbols_list, current_address_value);
            add_to_memory(current_address_value, &counter, symbol_word, memory);
        }
        else {
            (*current_address_value)++;
        }
        break;
    }
 }
    return 1;
}
