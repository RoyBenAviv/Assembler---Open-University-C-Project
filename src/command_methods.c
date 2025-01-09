#include "data.h"


void initialize_opcodes(Opcode opcodes[]) {
    Opcode temp_opcodes[] = {
        { "mov", {1, 1, 1, 1}, {0, 1, 1, 1}, 1 },
        { "cmp", {1, 1, 1, 1}, {1, 1, 1, 1}, 1 },
        { "add", {1, 1, 1, 1}, {0, 1, 1, 1}, 1 },
        { "sub", {1, 1, 1, 1}, {0, 1, 1, 1}, 1 },
        { "lea", {0, 1, 0, 0}, {0, 1, 1, 1}, 1 },
        { "clr", {0, 0, 0, 0}, {0, 1, 1, 1}, 2 },
        { "not", {0, 0, 0, 0}, {0, 1, 1, 1}, 2 },
        { "inc", {0, 0, 0, 0}, {0, 1, 1, 1}, 2 },
        { "dec", {0, 0, 0, 0}, {0, 1, 1, 1}, 2 },
        { "jmp", {0, 0, 0, 0}, {0, 1, 1, 0}, 2 },
        { "bne", {0, 0, 0, 0}, {0, 1, 1, 0}, 2 },
        { "red", {0, 0, 0, 0}, {0, 1, 1, 1}, 2 },
        { "prn", {0, 0, 0, 0}, {1, 1, 1, 1}, 2 },
        { "jsr", {0, 0, 0, 0}, {0, 1, 1, 0}, 2 },
        { "rts", {0, 0, 0, 0}, {0, 0, 0, 0}, 3 },
        { "stop", {0, 0, 0, 0}, {0, 0, 0, 0}, 3 }
    };

    memcpy(opcodes, temp_opcodes, sizeof(temp_opcodes));
}


void initialize_words(char** first_word, char** first_external_word, char** second_external_word, char** combined_external_word) {
    *first_word = convert_to_bits_representation(0, 15);
    *first_external_word = convert_to_bits_representation(0, 15);
    *second_external_word = convert_to_bits_representation(0, 15);
    *combined_external_word = convert_to_bits_representation(0, 15);
}


int find_opcode_idx(char* str, Opcode opcodes[]) {
    int i;

    for (i = 0; i < OPCODES_LENGTH; i++) {
        if (strcmp(str, opcodes[i].name) == 0) {
            return i;
        }
    }
    return -1;
}
void parse_operands(char* str, char** first_operand, char** second_operand) {


    *first_operand = strtok(NULL, ",");

    if (*first_operand != NULL) {
        trim(*first_operand);
    }

    *second_operand = strtok(NULL, ",");
    if (*second_operand != NULL) {
        trim(*second_operand);
    }
}

int find_addressing_method(char* operand, LinkedList* symbols_list) {
    if (operand == NULL) {
        return -1;
    }
    if (operand[0] == '#') {
        return 0;
    }
    else if (operand[0] == '*') {
        return 2;
    }
    else if (is_register(operand[0], operand[1])) { /* in case there is register included in the string, register is between 0-7 start with an 'r' */

        return 3;
    }
    else if (is_string_exists(symbols_list, operand)) {
        return 1;
    }
    else {
        return -2;
    }
}

int check_operands(Opcode opcode, int first_operand_method, int second_operand_method) {

    switch (opcode.group_number) {
    case 1: /*First operands group*/

        if (first_operand_method == -1) {
            printf("Source operand is mandatory: %d\n", first_operand_method);
            return 0;
        }

        if (second_operand_method == -1) {
            printf("Target operand is mandatory: %d\n", second_operand_method);
            return 0;
        }

        if (first_operand_method != -2 && opcode.source_methods[first_operand_method] == 0) {
            printf("Illegal source %d operand method for %s opcode.\n", first_operand_method, opcode.name);
            return 0;
        }

        if (second_operand_method != -2 && opcode.target_methods[second_operand_method] == 0) {
            printf("Illegal target %d operand method for %s opcode.\n", second_operand_method, opcode.name);
            return 0;
        }
        break;

    case 2: /*Second operands group*/

        if (first_operand_method == -1) {
            printf("Target operand is mandatory: %d\n", first_operand_method);
            return 0;
        }

        if (second_operand_method != -1) {
            printf("Illegal second %d operand method for %s opcode.\n", second_operand_method, opcode.name);
            return 0;
        }

        if (first_operand_method != -2 && opcode.target_methods[first_operand_method] == 0) {
            printf("Illegal target %d operand method for %s opcode.\n", first_operand_method, opcode.name);
            return 0;
        }
        break;

    case 3: /*Third operands group*/
        if (first_operand_method != -1) {
            printf("Illegal method %d operand method for %s opcode.\n", first_operand_method, opcode.name);
            return 0;
        }
        break;

    default:
        printf("Issue on reading group \n");
        return 0;
    }
    return 1;
}

char* get_external_word(int operand_method, const char* operand, const char* type, LinkedList* symbols_list) {
    char* external_word;
    char* bits;
    char* are_field;
    int number;
    unsigned int converted_number;
    int error;
    int register_number;

    external_word = NULL;
    bits = NULL;
    are_field = NULL;

    switch (operand_method) {
    case 0: {
        error = 0;
        number = extract_number(operand, '#', &error);
        if (error) {
            printf("Error: unable to extract number\n");
            return NULL;
        }
        converted_number = convert_by_twos_complement(number);
        bits = convert_to_bits_representation(converted_number, 12);
        are_field = convert_to_bits_representation(4, 3);
        external_word = (char*)malloc(strlen(bits) + strlen(are_field) + 1);
        if (external_word == NULL) {
            printf("Error: memory allocation failed\n");
            return NULL;
        }

        strcpy(external_word, bits);
        strcat(external_word, are_field);

        break;
    }
    case 2:
    case 3: {
        error = 0;
        register_number = extract_number(operand, operand_method == 2 ? '*' : 'r', &error);
        if (error) {
            printf("Error: unable to extract number\n");
            return NULL;
        }
        external_word = convert_to_bits_representation(0, 15);
        bits = convert_to_bits_representation(register_number, 3);
        external_word[12] = '1'; /* A */

        if (strcmp(type, SOURCE) == 0) {
            replace_substring(external_word, 6, 8, bits);
        }
        else if (strcmp(type, TARGET) == 0) {
            replace_substring(external_word, 9, 11, bits);
        }
        else {
            printf("Unknown type: %s\n", type);
            break;
        }
        break;
    }
    default:
        external_word = NULL;
        break;
    }

    free(bits);
    free(are_field);

    return external_word;
}

char* get_symbol_word(char* operand, LinkedList* symbols_list, int * current_address_value) {
    char* external_word;
    char* bits;
    ListNode* symbol;

    external_word = NULL;
    bits = NULL;

    symbol = get_symbol(symbols_list, operand);
    if (symbol == NULL) {
        printf("Symbol not found: %s\n", operand);
        return NULL;
    }

    if (strcmp(symbol->instruction, ".extern") == 0) {
        external_word = convert_to_bits_representation(0, 15);
        external_word[14] = '1';
        update_symbol_value(symbols_list, symbol->name, (*current_address_value));
    }
    else {
        external_word = convert_to_bits_representation(0, 15);
        bits = convert_to_bits_representation(symbol->value, 12);
        external_word[13] = '1'; /*R*/
        replace_substring(external_word, 0, 11, bits);
    }

    return external_word;
}

int get_operand_method_pos(char* type, int operand_method) {
    int pos_type;

    if (operand_method == -1) return -1;


    if (strcmp(type, SOURCE) == 0) {
        pos_type = 0;
    }
    else if (strcmp(type, TARGET) == 0) {
        pos_type = 1;
    }
    else {
        return -1;
    }

    switch (operand_method) {
    case -2:
    case 1:
        return pos_type ? 10 : 6;
    case 0:
        return pos_type ? 11 : 7;
    case 2:
        return pos_type ? 9 : 5;
    case 3:
        return pos_type ? 8 : 4;
    default:
        return -1;
    }
}

void handle_first_word(char** first_word, int source_operand_method, int target_operand_method, int opcode_idx) {
    char* command_bits;
    int source_pos;
    int target_pos;

    command_bits = convert_to_bits_representation(opcode_idx, 4);

    source_pos = get_operand_method_pos(SOURCE, source_operand_method);
    target_pos = get_operand_method_pos(TARGET, target_operand_method);


    (*first_word)[12] = '1';
    replace_substring(*first_word, 0, 3, command_bits);
    if (source_pos != -1)
        (*first_word)[source_pos] = '1';
    if (target_pos != -1)
        (*first_word)[target_pos] = '1';

}

void handle_external_words(char** first_external_word, char** second_external_word, int source_operand_method, int target_operand_method, char* first_operand, char* second_operand, LinkedList* symbols_list) {

    if (source_operand_method != -1) {
        if (source_operand_method == -2 || source_operand_method == 1) *first_external_word = "?";
        else *first_external_word = get_external_word(source_operand_method, first_operand, "source", symbols_list);
    }

    if (target_operand_method != -1) {
        if (target_operand_method == -2 || target_operand_method == 1) *second_external_word = "?";
        else *second_external_word = get_external_word(target_operand_method, second_operand, "target", symbols_list);
    }

}

void handle_combined_external_word(char** combined_external_word, int first_operand_method, int second_operand_method, char* source_operand, char* target_operand) {
    char* external_word;
    char* source_bits;
    char* target_bits;
    int source_register_number;
    int target_register_number;
    int error;

    external_word = convert_to_bits_representation(0, 15);
    external_word[12] = '1'; /* A */

    error = 0;
    source_register_number = extract_number(source_operand, first_operand_method == 2 ? '*' : 'r', &error);
    if (error) {
        printf("Error: unable to extract number\n");
        return;
    }
    source_bits = convert_to_bits_representation(source_register_number, 3);


    target_register_number = extract_number(target_operand, second_operand_method == 2 ? '*' : 'r', &error);

    if (error) {
        printf("Error: unable to extract number\n");
        return;
    }
    target_bits = convert_to_bits_representation(target_register_number, 3);

    replace_substring(external_word, 6, 8, source_bits);
    replace_substring(external_word, 9, 11, target_bits);

    *combined_external_word = external_word;
}
