#define MIN_NUMBER -2048
#define MAX_NUMBER 2047

/*
  Function: convert_to_bits_representation

  This function converts an int to a binary string.

  Number: int to convert.
  Bits: number of bits in binary string.

  Returns a string containing the binary of the number.
*/
char* convert_to_bits_representation(unsigned int number, int bits);

/*
  Function: convert_by_twos_complement
  Converts an integer to its 12-bit two complement.

  Number: int to convert.

  Returns the unsigned integer of the 12-bit two complement of the number.
  If the number is out of range for 12-bit two complement, returns 0 and prints an error message.
*/
unsigned int convert_by_twos_complement(int number);

/*
  Function: convert_string_to_ascii
  Transforms a string into its ascii binary form and saves it in memory.

  Str: the string to be converted.
  Data_counter: pointer to track data count.
  Current_address_value: pointer to keep track of address value.
  Memory: memory array.

  This function encodes each character of the string into a 15-bit binary format
  and places it into the memory array.
*/
void convert_string_to_ascii(char* str, int* data_counter, int* current_address_value, char** memory);

/*
  Function: convert_number_to_ascii
  Converts a string of numbers separated by commas to ascii binary and stores them in memory.

  Str: input string containing the numbers.
  Data_counter: pointer to data counter.
  Current_address_value: pointer to current address value.
  Memory: array representing the memory.

  This function converts each number in the string to its 15-bit binary representation
  and stores it in memory.
*/
void convert_number_to_ascii(char* str, int* data_counter, int* current_address_value, char** memory);

/*
  Function: binary_to_octal
  Converts a binary string to its octal representation.

  Binary: binary string to be converted.

  Returns a string containing the octal representation of the binary string.
  The caller is responsible for freeing the allocated memory.
*/
char* binary_to_octal(char* binary);

