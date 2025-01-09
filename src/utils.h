#ifndef UTILS_H
#define UTILS_H

#define MAX_NUM_SIZE 5

/*
  Function: ltrim
  Removes leading whitespace characters from the beginning of a string.

  Str: string to be trimmed.
 */
void ltrim(char* str);

/*
  Function: rtrim
  Removes trailing whitespace characters from the end of a string.

  Str: string to be trimmed.
 */
void rtrim(char* str);

/*
  Function: trim
  Removes leading and trailing whitespace characters from a string.

  Str: string to be trimmed.
 */
void trim(char* str);

/*
  Function: extract_number
  Extracts a number from a string.

  Str: string to be searched.
  Type: character that precedes the number in the string.
  Error: pointer to an integer that will be set to 1 if an error occurs, 0 otherwise.

  Returns the extracted number.
*/
int extract_number(const char* str, char type, int* error);

/*
  Function: replace_substring
  Replaces a substring in a string with another string.

  Str: original string.
  Start_index: starting index of the substring to be replaced.
  End_index: ending index of the substring to be replaced.
  Replacement: substring to replace with.

  This function modifies the original string in place.
*/
void replace_substring(char* str, int start_index, int end_index, const char* replacement);

/*
  Function: extract_first_word
  Extracts the first word from a string and returns the remaining string.

  Str: input string.
  First_word: extracted first word.

  Returns the remaining string after the first word.
*/
char* extract_first_word(char* input, char* output);

/*
  Function: concat_str
  Concatenates a string with another string.

  Str: original string.
  Part: part to be concatenated.

  Returns the concatenated string.
*/
char* concat_str(char* str, char* part);

/*
  Function: is_register
  Checks if two characters represent a register.

  FirstChar: first character.
  SecondChar: second character.

  Returns 1 if the characters represent a register, 0 otherwise.
*/
int is_register(char firstChar, char secondChar);

/*
  Function: is_line_empty_or_comment
  Checks if a line is empty or a comment.

  Buffer: line to be checked.
*/
int is_line_empty_or_comment(char* buffer);

/*
  Function: extract_first_word_dynamic
  Extracts the first word from a string dynamically.

  Str: input string.

  Returns a dynamically allocated string containing the first word.
*/
char* extract_first_word_dynamic(char* str);

/*
  Function: extract_second_word_dynamic
  Extracts the second word from a string dynamically.

  Str: input string.

  Returns a dynamically allocated string containing the second word.
*/
char* extract_second_word_dynamic(char* str);

/*
  Function: duplicate_string_dynamic
  Duplicates a string dynamically.

  Inputstr: string to duplicate.

  Returns a dynamically allocated copy of the input string.
*/
char* duplicate_string_dynamic(char* inputstr);

#endif

