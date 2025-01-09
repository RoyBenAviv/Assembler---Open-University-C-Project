#ifndef LINKEDLIST_H
#define LINKEDLIST_H


typedef struct ListNode {
    char* name;
    char* instruction;
    int value;
    struct ListNode* next;
} ListNode;

typedef struct LinkedList {
    ListNode* head;
} LinkedList;


/*
  Function: add_symbol
  Adds a symbol to the symbol list.

  Symbols_list: pointer to the linked list of symbols.
  Symbol_name: name of the symbol to be added.
  Current_address_value: pointer to the current address value.
  Instruction: the instruction associated with the symbol.
*/
void add_symbol(LinkedList* symbols_list, char* symbol_name, int* current_address_value, char* instruction);

/*
  Function: update_symbol_instruction
  Updates the instruction associated with a symbol in the symbol list.

  Symbols_list: pointer to the linked list of symbols.
  Symbol_name: name of the symbol to be updated.
  Instruction: the new instruction to be associated with the symbol.
*/
void update_symbol_instruction(LinkedList* symbols_list, char* symbol_name, char* instruction);

/*
  Function: update_symbol_value
  Updates the value associated with a symbol in the symbol list.

  Symbols_list: pointer to the linked list of symbols.
  Symbol_name: name of the symbol to be updated.
  Value: the new value to be associated with the symbol.
*/
void update_symbol_value(LinkedList* symbols_list, char* symbol_name, int value);

/*
  Function: is_symbol
  Checks if the given string represents a symbol.

  First_str_part: the string to be checked.

  Returns: 1 if the string is a symbol, 0 otherwise.
*/
int is_symbol(char* first_str_part);

/*
  Function: create_node
  Creates a new node for the symbol list.

  Str: the name of the symbol.
  Value: the value associated with the symbol.
  Str2: the instruction associated with the symbol.

  Returns: a pointer to the newly created node.
*/
ListNode* create_node(char* name, int value, char* instruction);

/*
  Function: is_string_exists
  Checks if a given string exists in the symbol list.

  List: pointer to the linked list of symbols.
  Str: the string to be checked.

  Returns: 1 if the string exists, 0 otherwise.
*/
int is_string_exists(LinkedList* list, char* str);

/*
  Function: get_symbol
  Retrieves a symbol node from the symbol list by its name.

  List: pointer to the linked list of symbols.
  Str: the name of the symbol to be retrieved.

  Returns: a pointer to the symbol node if found, NULL otherwise.
*/
ListNode* get_symbol(LinkedList* list, char* str);

/*
  Function: get_symbol_by_value
  Retrieves a symbol node from the symbol list by its value.

  List: pointer to the linked list of symbols.
  Value: the value of the symbol to be retrieved.

  Returns: a pointer to the symbol node if found, NULL otherwise.
*/
ListNode* get_symbol_by_value(LinkedList* list, int value);

/*
  Function: print_list
  Prints all symbols in the symbol list.

  List: pointer to the linked list of symbols.
*/
void print_list(LinkedList* list);

/*
  Function: contains_instruction
  Checks if any symbol in the list contains the given instruction.

  List: pointer to the linked list of symbols.
  Instruction: the instruction to be checked.

  Returns: 1 if the instruction is found, 0 otherwise.
*/
int contains_instruction(LinkedList* list, char* instruction);

/*
  Function: write_instruction_to_file
  Writes all symbols with a specific instruction to a file.

  List: pointer to the linked list of symbols.
  Instruction: the instruction to filter symbols by.
  File_name: the name of the file to write to.
*/
void write_instruction_to_file(LinkedList* list, char* instruction, char* file_name, char* type);

/*
  Function: print_symbol_list_to_file
  Writes all symbols with .extern or .entry instructions to their files.

  List: pointer to the linked list of symbols.
*/
void print_symbol_list_to_file(LinkedList* list, char* file_name, int file_name_length);

#endif /* LINKEDLIST_H */

