#include "link_list.h"
#define LINE_LENGTH 80

/*
  Function: process_command_first_pass
  Processes a command during the first pass, updating the instruction counter,
  current address value, and memory.

  Str: the input string containing the command to process.
  Instruction_counter: pointer to the instruction counter.
  Current_address_value: pointer to the current address value.
  Symbols_list: pointer to the list of symbols.
  Memory: the array representing the memory.
*/
int process_command_first_pass(char* str, int* instruction_counter, int* current_address_value, LinkedList* symbols_list, char** memory);

/*
  Function: process_command_second_pass
  Processes a command during the second pass, updating the current address value
  and memory with symbol information.

  Str: the input string containing the command to process.
  Current_address_value: pointer to the current address value.
  Symbols_list: pointer to the list of symbols.
  Memory: the array representing the memory.
*/
int process_command_second_pass(char* str, int* current_address_value, LinkedList* symbols_list, char** memory);

/*
  Function: handle_group1
  Handles commands that belong to group 1 opcode, updating the current address value,
  instruction counter, and memory.

  This function processes commands with two operands, determines whether a combined
  external word or separate external words are needed, and updates the memory accordingly.
*/
void handle_group1(int* current_address_value, int* instruction_counter, char* first_word, char* first_external_word, char* second_external_word, char* combined_external_word, int first_operand_method, int second_operand_method, int opcode_idx, char* first_operand, char* second_operand, char** memory, LinkedList* symbols_list);

/*
  Function: handle_group2
  Handles commands that belong to group 2 opcode, updating the current address value,
  instruction counter, and memory.

  This function processes commands with one operand, determines the addressing method,
  and updates the memory accordingly.
*/
void handle_group2(int* current_address_value, int* instruction_counter, char* first_word, char* first_external_word, char* second_external_word, int first_operand_method, int opcode_idx, char* first_operand, char** memory, LinkedList* symbols_list);

/*
  Function: handle_group3
  Handles commands that belong to group 3 opcode, updating the current address value,
  instruction counter, and memory.

  This function processes commands with no operands and updates the memory accordingly.
*/
void handle_group3(int* current_address_value, int* instruction_counter, char* first_word, int opcode_idx, char** memory);

