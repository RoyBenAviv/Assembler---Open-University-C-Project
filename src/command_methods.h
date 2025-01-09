#include "link_list.h"
#define OPCODES_LENGTH 16
#define SOURCE "source"
#define TARGET "target"

typedef struct {
    const char* name;
    int source_methods[4];
    int target_methods[4];
    int group_number;
} Opcode;

/*
  Function: initialize_opcodes
  Initializes the array of opcodes with predefined values.

  Opcodes: array of Opcode structures to be initialized.
*/
void initialize_opcodes(Opcode opcodes[]);

/*
  Function: initialize_words
  Initializes words to 15 characters of bits of zeros.

  First_word: pointer to the first word.
  First_external_word: pointer to the first external word.
  Second_external_word: pointer to the second external word.
  Combined_external_word: pointer to the combined external word.
*/
void initialize_words(char** first_word, char** first_external_word, char** second_external_word, char** combined_external_word);

/*
  Function: find_opcode_idx
  Finds the index of an opcode in the opcodes array.

  Str: name of the opcode to be found.
  Opcodes: array of Opcode structures.

  Returns: index of the opcode if found, -1 otherwise.
*/
int find_opcode_idx(char* str, Opcode opcodes[]);

/*
  Function: parse_operands
  Parses the operands from a given string.

  Str: string containing operands.
  First_operand: pointer to the first operand.
  Second_operand: pointer to the second operand.
*/
void parse_operands(char* str, char** first_operand, char** second_operand);

/*
  Function: find_addressing_method
  Determines the addressing method of an operand.

  Operand: the operand string.
  Symbols_list: pointer to the linked list of symbols.

  Returns: addressing method of the operand.
*/
int find_addressing_method(char* operand, LinkedList* symbols_list);

/*
  Function: check_operands
  Validates the operand methods for a given opcode.

  Opcode: the opcode to validate.
  First_operand_method: method of the first operand.
  Second_operand_method: method of the second operand.

  Returns: 1 if operands are valid, 0 otherwise.
*/
int check_operands(Opcode opcode, int first_operand_method, int second_operand_method);

/*
  Function: get_external_word
  Gets the external word based on its addressing method.

  Operand_method: addressing method of the operand.
  Operand: the operand string.
  Type: type of operand (SOURCE or TARGET).
  Symbols_list: pointer to the linked list of symbols.

  Returns: external word representation as a string.
           NULL if an error occurs.
*/
char* get_external_word(int operand_method, const char* operand, const char* type, LinkedList* symbols_list);

/*
  Function: get_symbol_word
  Gets the external word for a symbol.

  Operand: the operand string (symbol).
  Symbols_list: pointer to the linked list of symbols.
  Current_address_value: pointer to the current address value.

  Returns: external word representation as a string.
           NULL if the symbol is not found or an error occurs.
*/
char* get_symbol_word(char* operand, LinkedList* symbols_list, int* current_address_value);

/*
  Function: get_operand_method_pos
  Gets the bit position for an operand method in the first word.

  Type: type of operand (SOURCE or TARGET).
  Operand_method: addressing method of the operand.

  Returns: bit position for the operand method.
           -1 if the type or method is invalid.
*/
int get_operand_method_pos(char* type, int operand_method);

/*
  Function: handle_first_word
  Updates the first word with the opcode and operand methods.

  First_word: pointer to the first word.
  Source_operand_method: method of the source operand.
  Target_operand_method: method of the target operand.
  Opcode_idx: index of the opcode.
*/
void handle_first_word(char** first_word, int source_operand_method, int target_operand_method, int opcode_idx);

/*
  Function: handle_external_words
  Updates the external word for the source and target operands.

  First_external_word: pointer to the first external word.
  Second_external_word: pointer to the second external word.
  Source_operand_method: method of the source operand.
  Target_operand_method: method of the target operand.
  First_operand: the first operand string.
  Second_operand: the second operand string.
  Symbols_list: pointer to the linked list of symbols.
*/
void handle_external_words(char** first_external_word, char** second_external_word, int source_operand_method, int target_operand_method, char* first_operand, char* second_operand, LinkedList* symbols_list);

/*
  Function: handle_combined_external_word
  Updates the combined external word for source and target operands.

  Combined_external_word: pointer to the combined external word.
  First_operand_method: method of the first operand.
  Second_operand_method: method of the second operand.
  Source_operand: the source operand string.
  Target_operand: the target operand string.
*/
void handle_combined_external_word(char** combined_external_word, int first_operand_method, int second_operand_method, char* source_operand, char* target_operand);


