#include "data.h"

int extract_number(const char* str, char type, int* error) {
    char* start;
    char number_str[MAX_NUM_SIZE];
    char* ptr;
    int number;

    start  = strchr(str, type);
    if (start == NULL) {
        *error = 1;
        return 0; 
    }

    start++;
    while (*start && !isdigit(*start)) {
        if (*start == '-') {
            start++;
            continue; /* Skip '-' and check next character */
        }
        start++;
    }

    
    ptr = start;
    while (*ptr && isdigit(*ptr)) {
        ptr++;
    }

    if (ptr == start) {
        *error = 1;
        return 0;
    }

    strncpy(number_str, start, ptr - start);
    number_str[ptr - start] = '\0';

    number = atoi(number_str);

    /*Check if the number negative */
    if (*(start - 1) == '-') {
        number *= -1;
    }

    return number;
}

void ltrim(char* str) {
    char* start = str;
    char* dest = str;

    while (*start && (*start == ' ' || *start == '\n' || *start == '\r' || *start == '\t')) {
        start++;
    }

    while (*start) {
        *dest++ = *start++;
    }

    *dest = '\0';
}

void rtrim(char* str) {
    int len = strlen(str);

    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n' || str[len - 1] == '\r' || str[len - 1] == '\t')) {
        str[len - 1] = '\0';
        len--;
    }
}

void trim(char* str) {
    ltrim(str);
    rtrim(str);
}

void replace_substring(char* str, int start_index, int end_index, const char* replacement) {
    int original_length; 
    int replacement_length; 
    int replace_length; 
    int new_length;
    int i, j;

    original_length = strlen(str);
    replacement_length = strlen(replacement);
    replace_length = end_index - start_index + 1;

    /*Check if indices are valid */
    if (start_index < 0 || end_index >= original_length || start_index > end_index) {
        printf("Invalid indices");
        return;
    }

    /* Calculate new length of the string after replacement */
    
    new_length = original_length - replace_length + replacement_length;


    for (i = end_index + 1, j = start_index + replacement_length; i <= original_length; ++i, ++j) {
        str[j] = str[i];
    }

    for (i = 0; i < replacement_length; ++i) {
        str[start_index + i] = replacement[i];
    }
    
    str[new_length] = '\0';
}

char* extract_first_word(char* str, char* first_word) {
    while (*str && !isspace((unsigned char)*str)) {
        *first_word++ = *str++;
    }
    *first_word = '\0';

    /* skip the spaces after the first word */
    while (isspace((unsigned char)*str)) str++;

    return str;
}

char* concat_str(char* str, char * part) {
    char* concated_str;
    concated_str = strtok(str, part);
    return concated_str;
}

int is_register(char firstChar, char secondChar) {
    /*Check if the first character is 'r' and the second character is between '0' and '7'*/
    return firstChar == 'r' && (secondChar >= '0' && secondChar <= '7');
}

int is_line_empty_or_comment(char* buffer) {
    return buffer[0] == '\0' || buffer[0] == ';';
}

char* extract_first_word_dynamic(char* str) {
    /* this function get a string as an input, extract first word (without whitespaces) and return pointer to new word
    (dynamic allocated, free meamory alocated after use in needed)*/
    
    int counter;
    int length;
    char* first_word;
    char* end;



    /* skip whitespace */
    while (*str && isspace((char)*str)) {
        str++;
    }

    /* if string is empty or contains only spaces */
    if (*str == '\n') {
        return "\n";
    }

    /* find the end of first word */
    end = str;
    while (*end && !isspace((char)*end)) {
        end++;
    }

    /* allocate memory for new string */
    length = (int)(end - str);
    first_word = (char*)malloc(length + 1);
    if (first_word == NULL) {
        printf("memory allocation fail! extract_first_word2 function");
        return NULL;
    }

    /* copy first word to allocated meamory */
    for (counter = 0; counter < length; counter++) {
        first_word[counter] = str[counter];
    }
    first_word[length] = '\0'; /* Null - terminate new string */

    return first_word;
}
char* extract_second_word_dynamic(char* str) {
    /*this function get a string as an input, extract second word (without whitespaces) and return pointer to new word 
    (dynamic allocated, free meamory alocated after use in needed)*/
    char* end;
    int length;
    char* second_word;



    /* skip whitespace */
    while (*str && isspace((char)*str)) 
        str++;
    

    /* skip first word */
    while (*str && !isspace((char)*str)) 
        str++;
    

    /* skip whitespace between first word and second word */
    while (*str && isspace((char)*str)) 
        str++;
    

    /* if there is second word */
    if (*str == '\0') 
        return NULL;
    

    /* find the end of second word */
    end = str;
    while (*end && !isspace((char)*end)) 
        end++;
    

    /* sllocate memory for second word */
    length = end - str;

    second_word= (char*)malloc(length + 1);
    if (second_word == NULL) {
        printf("Error allocating memory");
        return NULL;
    }

    /* copy second word to allocated memory */
    strncpy(second_word, str, length);
    second_word[length] = '\0';

    return second_word;
}
char* duplicate_string_dynamic(char* inputstr)  {
/*this function duplicate input string to new dynamic allocated string, and return pointer to new string (dynamiclly allocated, need to use 'free' after use) */
    char* outputStr;

    outputStr = (char*)malloc(strlen(inputstr) + 1); /* +1 for '\0' */
    if (outputStr == NULL) {
        printf("meamory allocation falied! exit program");
        exit(1);
    }

    strcpy(outputStr, inputstr);
    
    return outputStr;
}

