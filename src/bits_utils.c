#include "data.h"

char* convert_to_bits_representation(unsigned int number, int bits) {
    char* bit_string;
    int i;
    bit_string = (char*)malloc(bits + 1);  /*Allocate memory for the bit string */
    if (bit_string == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    bit_string[bits] = '\0'; 

    for (i = bits - 1; i >= 0; i--) {
        bit_string[i] = (number & 1) ? '1' : '0'; /*Convert each bit of the number to 1 or 0 */
        number >>= 1; /*Shift number right by 1 bit*/
    }

    return bit_string;
}

unsigned int convert_by_twos_complement(int number) {
    if (number < MIN_NUMBER || number > MAX_NUMBER) {
        printf("Number out of range for 12-bit two's complement: %d\n", number);
        return 0;
    }

    if (number < 0) {
        number = (1 << 12) + number; /*Compute two's complement if negative */
    }

    return (unsigned int)number; /* Return unsigned int representation */
}

void convert_string_to_ascii(char* str, int* data_counter, int * current_address_value, char** memory) {
    int length;
    char* bits;
    int i;

    length = strlen(str);

    if (str[0] == '"' && str[length - 1] == '"') {
        for (i = 1; i < strlen(str) - 1; i++) {

            bits = convert_to_bits_representation((int)str[i], 15);
            add_to_memory(current_address_value, data_counter, bits, memory);
        }

        
        bits = convert_to_bits_representation((int)'\0', 15);
        add_to_memory(current_address_value, data_counter, bits, memory);
    }
}

void convert_number_to_ascii(char* str, int* data_counter, int* current_address_value, char** memory) {
    char* token;
    char* bits;
    int number;

    token = strtok(str, ",");

    while (token != NULL) {
        trim(token);
        number = atoi(token);
        bits = convert_to_bits_representation(number, 15);

        add_to_memory(current_address_value, data_counter, bits, memory);


        token = strtok(NULL, ",");
    }

}

char* binary_to_octal(char* binary) {
    int length = strlen(binary);
    int decimal;
    int i;
    char* octal;
    int octal_length;


	octal_length = 6; /* Octal length is 6 digits */
	decimal = 0;


    /* Convert binary string to decimal */
    for (i = 0; i < length; i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }


    octal = malloc(octal_length + 1);
    if (!octal) {
        return NULL; /* Memory allocation failed */
    }

    octal[octal_length] = '\0';
    for (i = octal_length - 1; i >= 0; i--) {
        octal[i] = (decimal % 8) + '0';
        decimal /= 8;
    }

    /* Fill in zeros */
    for (i = 0; i < octal_length && octal[i] == '\0'; i++) {
        octal[i] = '0';
    }

    return octal;
}
