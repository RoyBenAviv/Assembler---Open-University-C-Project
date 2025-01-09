#include "link_list.h"

/*
  Function: process_first_pass
  Processes the first pass of the file.

  Buffer: line of code to be processed.
  Instruction_counter: pointer to the instruction counter.
  Data_counter: pointer to the data counter.
  Current_address_value: pointer to the current address value.
  Symbols_list: pointer to the list of symbols.
  Memory: array representing the amemory.

  The function performs the initial process for the file after macro, gets the source code line by line, extracts symbols, and updates
  the memory.
*/
void process_first_pass(char* buffer, int* instruction_counter, int* data_counter, int* current_address_value, LinkedList* symbols_list, char** memory);

