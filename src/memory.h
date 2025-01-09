#define MEMORY_LENGTH 4092
#define MEMORY_START 100

/*
  Function: add_to_memory
  Adds a binary string representation to memory at the current address value.

  Current_address_value: pointer to the current address value.
  Counter: pointer to the counter to increment (data or instruction counter).
  Bits: the binary string to be added to memory.
  Memory: the array representing the memory.

  This function prints the address and the binary string being added, updates the memory, and
  increments the current address value.
*/
void add_to_memory(int* current_address_value, int* counter, char* bits, char** memory);

/*
  Function: print_memory_to_file
  Writes the memory contents to a file in octal representation.

  Size: the size of the memory array.
  Memory: the array representing the memory.
  Data_counter: the data counter value.
  Instruction_counter: the instruction counter value.
  File_name: the name of the file to write to.

  This function writes the instruction counter and data counter to the file,
  followed by each memory entry in octal representation.
*/
void print_memory_to_file(int size, char** memory, int data_counter, int instruction_counter, char* file_name);

