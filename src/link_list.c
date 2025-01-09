#include "data.h"

void add_symbol(LinkedList* symbols_list, char* symbol_name, int* current_address_value, char* instruction) {
    ListNode* symbol;
    symbol = create_node(symbol_name, *current_address_value, instruction);
    if (symbols_list->head == NULL) {
        symbols_list->head = symbol;
    }
    else {
        ListNode* current = symbols_list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = symbol;
    }
}

void update_symbol_instruction(LinkedList* symbols_list, char* symbol_name, char* instruction) {
    ListNode* symbol;
    symbol = get_symbol(symbols_list, symbol_name);
    if (symbol != NULL) {
        /*Attempt to reallocate memory for the instruction */
        char* temp;
        temp = realloc(symbol->instruction, strlen(instruction) + 1);
        if (temp == NULL) {
            printf("Error: Memory reallocation failed.\n");
            return;
        }
        symbol->instruction = temp;
        strcpy(symbol->instruction, instruction);
    }
}

void update_symbol_value(LinkedList* symbols_list, char* symbol_name, int value) {
    ListNode* symbol;
    symbol = get_symbol(symbols_list, symbol_name);
    if (symbol != NULL) {
        symbol->value = value;
    }
}


int is_symbol(char* first_str_part) {
    int length;
    length = strlen(first_str_part);
    return first_str_part[length - 1] == ':';
}

ListNode* create_node(char* str, int value, char* str2) {
    ListNode* node;
    node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->name = (char*)malloc(strlen(str) + 1);
    node->instruction = (char*)malloc(strlen(str2) + 1);
    if (!node->name) {
        fprintf(stderr, "Memory allocation for name failed\n");
        exit(EXIT_FAILURE);
    }
    if (!node->instruction) {
        fprintf(stderr, "Memory allocation for instruction failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(node->name, str);
    strcpy(node->instruction, str2);
    node->value = value;
    node->next = NULL;

    return node;
}

int is_string_exists(LinkedList* list, char* str) {
    ListNode* current;

    if (is_register(str[0], str[1])) {
        printf("Register can't be a symbol! \n");
        return 0;
    }


    current = list->head;
    while (current != NULL) {
        if (strcmp(current->name, str) == 0) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}


ListNode* get_symbol(LinkedList* list, char* str) {
    ListNode* current;

    current = list->head;
    while (current != NULL) {
        if (strcmp(current->name, str) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

ListNode* get_symbol_by_value(LinkedList* list, int value) {
    ListNode* current;

    current = list->head;
    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void print_list(LinkedList* list) {
    ListNode* current;

    current  = list->head;
    current == NULL ? printf("Symbol list is empty.\n") : printf("Symbol list:\n");
   
    
    while (current != NULL) {
        printf("Name: %s, Instruction: %s, Address Value: %d\n", current->name, current->instruction, current->value);
        current = current->next;
    }
}

int contains_instruction(LinkedList* list, char* instruction) {
    ListNode* current;
    current = list->head;
    while (current != NULL) {
        if (strcmp(current->instruction, instruction) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void write_instruction_to_file(LinkedList* list, char* instruction, char* file_name, char* type) {
    FILE* file;
    ListNode* current;

    file = fopen(strcat(file_name, type), "w");
    if (file == NULL) {
        printf("Failed to open file");
        return;
    }

    current = list->head;
    while (current != NULL) {
        if (strcmp(current->instruction, instruction) == 0) {
            fprintf(file, "%s \t %d\n", current->name, current->value);
        }
        current = current->next;
    }

    fclose(file);
    printf("Data written to %s successfully.\n", file_name);
}

void print_symbol_list_to_file(LinkedList* list, char* file_name, int file_name_length) {
    if (contains_instruction(list, ".extern")) {
        write_instruction_to_file(list, ".extern", file_name, ".ext");
	(file_name)[file_name_length] = '\0';
    }
    if (contains_instruction(list, ".entry")) {
        write_instruction_to_file(list, ".entry", file_name, ".ent");
	(file_name)[file_name_length] = '\0';
    }
}

