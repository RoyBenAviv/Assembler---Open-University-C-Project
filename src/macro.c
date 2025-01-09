#include "data.h"

Line * create_new_line_node(char * input_line) {

    /*this function get an input of string,  create new struct Line node and set Line->line_content pointer to point on input string. return new Line node */

    Line * new_line;

    new_line = (Line * ) malloc(sizeof(Line));

    if (new_line == NULL)
        return NULL; /* meamory allocation fail */

    new_line -> line_content = duplicate_string_dynamic(input_line);
    if (new_line -> line_content == NULL)
        return NULL; /* meamory allocation fail! */

    new_line -> next = NULL;

    return new_line;

}

int add_line_node_to_macro(Macro * macro_node, Line * new_line_node) {

    /*this function get for input Macro node and Line node, and add new line node to end of linked list of Lines

    thats stored in Macro node. return -1 for fail and 0 for success*/

    if (macro_node == NULL || new_line_node == NULL) 
        return -1; /* meamory allocation fail! */

    

    /*  if first line of macro definition */

    if (macro_node -> macro_line_list == NULL) {
        macro_node -> macro_line_list = new_line_node;

    } else {

        Line * current;

        current = macro_node -> macro_line_list;

        while (current -> next != NULL) 
            current = current -> next;


        current -> next = new_line_node;

    }

    return 0;

}

Macro * create_new_macro_node(char * name) {

    /*this function get an input of string that is the new macro name,  create new struct Macro node and set Macro->name pointer to

    point on input string duplicated (macro name). return new Macro node. returned Macro->name needs to be free*/

    Macro * new_macro = (Macro * ) malloc(sizeof(Macro));

    if (new_macro == NULL) 
        return NULL; /* memory allocation fails! (Macro* newMacro node) */

    
    new_macro -> name = duplicate_string_dynamic(name);

    if (new_macro -> name == NULL) {
        free(new_macro);
        return NULL; /* memory allocation fails! (Macro* newMacro-> name) */
    }


    new_macro -> macro_line_list = NULL;
    new_macro -> next = NULL;

    return new_macro; /* return pointer to new macro node */

}

int add_macro_node_to_end(Macro ** head, Macro * new_macro_node) {

    /* this function get for input Macro node and Macro linked list head pointer, and add new Macro node to end of linked list of Macro nodes.

    return -1 for fail and 0 for success*/

    Macro * cur_macro;

    if (new_macro_node == NULL) 
        return -1;

 
    new_macro_node -> next = NULL; /* new node is last node   */


    if ( * head == NULL) {

        * head = new_macro_node; /* if list empty, set new node as head */

    } else {
        /* find the end of the listand add the new node */

        cur_macro = * head;

        while (cur_macro -> next != NULL)

            cur_macro = cur_macro -> next;

        cur_macro -> next = new_macro_node;

    }

    return 0;

}

int check_if_macro_name_is_command(char * word, char * commands_arr[], int arr_size) {

    /* this function gets for input a word, array of words and the size of array (how many string elemets), 

    and check if word is equals one the array string elements (if found given word in words array).

    return -1 for error and 0 for success*/

    int counter;

    for (counter = 0; counter < arr_size; counter++)

        if (strcmp(word, commands_arr[counter]) == 0)

            return 1; /* if found command that have the same name as macro */

    return 0;

}

Macro * serach_macro_in_list_by_name(Macro * head, char * macr_name) {

    /*this function get for input Macro linked list first node and string that is name to find, and search for Macro node with same name (Macro->name).

    return NULL if there is no Macro node named like that in linkes list, and if found Macro node with same name - return pointer to this Macro node.*/

    Macro * curr_macro;

    if (head == NULL)
        return NULL;

    curr_macro = head;

    while (curr_macro != NULL) {

        if (strcmp(curr_macro -> name, macr_name) == 0) 
            return curr_macro; /* Return the macro node(pointer) with matching name */

         else 
            curr_macro = curr_macro -> next;

        

    }

    return NULL; /* there is no macro with the matching name */

}

int write_opened_macro_to_file(FILE * output_file, Macro * macro_node) {

    /*this function get file pointer and Macro node, and write opened macro (linked list of Lines stored in Macro node) in the file given as input.

    return -1 for fail and 0 for success*/

    Line * buffer;

    if (output_file == NULL || macro_node == NULL)

        return -1; /* error!node is empty or file not valid.quit function without action and return -1 */

    buffer = macro_node -> macro_line_list;

    while (buffer != NULL) {
        /* print to new file each line of opened macro  */

        fprintf(output_file, "%s", buffer -> line_content);

        buffer = buffer -> next;

    }

    return 0; /* function succeeded! */

}


int free_macro_list_with_lines(Macro * macro_head) {

    /* this function get for input first element (head) of Macro linked list, and free the list including all fields inside each Macro node. */

    Macro * curr_macro;
    Macro * next;

    curr_macro = macro_head;

    while (curr_macro != NULL) {

        next = curr_macro -> next;

        free_Line_List(curr_macro -> macro_line_list); /* free Line list */

        free(curr_macro -> name); /* free macro name */

        free(curr_macro); /* free Macro node */

        curr_macro = next;

    }
    macro_head = NULL;
	
    return 0;

}

int free_Line_List(Line * head) {

    /*this get linked first element of linked list of Line nodes,  and free all elements of Line linked list with fields inside each node,

    return 0 for success.*/

    Line * current = head;

    Line * next;

    while (current != NULL) {

        next = current -> next;

        free(current -> line_content); /* free content of code line */

        free(current); /* free struct Line node */

        current = next;

    }

    return 0;

}

int proccess_macro_file(char * file_name) {

    /*VARIABLES */

    /* system commands array: */

    char * commands_arr[] = {
        "mov",
        "cmp",
        "add",
        "sub",
        "lea",
        "clr",
        "not",
        "inc",
        "dec",
        "jmp",
        "bne",
        "red",
        "prn",
        "jsr",
        "rts",
        "stop"
    };

    int commands_arr_size = sizeof(commands_arr) / sizeof(commands_arr[0]); /*number of elemets (string type) in commands array */
	
    char * macro_start_label = "macr\0";
	

    char * macr_end_label = "endmacr\0";

    Macro * macro_head = NULL; /* head of Macro* linked list */

    char buffer[LINE_MAX_LEN_WITH_NULL_TERMINATOR] = {
        0
    }; /* current line to proccess   */

	char * file_name_with_format;
    FILE * input_file;

    FILE * output_file;

    /* FILES: open input file, create / open new output file  */

    input_file = fopen(file_name, "r");

    if (input_file == NULL) {

        printf("Error opening input file! exit program\n");

        exit(1);

    }
	
	file_name_with_format = strcat(file_name, ".as");
    output_file = fopen(file_name_with_format, "w");

    if (output_file == NULL) {

        printf("Error Creating / opening output file! exit program\n");

        exit(1);

    }

    /* MAIN PROCCESS LOOP: read (from file) new line every iteration */

    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
char * first_word;
        /*  MAIN LOOP: read (from file) new line every iteration, and extract first word. 
        first word cases:
        case 1: first word is macro start label (create new macro, read lines to new macro till end label found).
        case 2: first word is a call for existing macro (write opened macro in output file).
        case 3: first word is not macro related (write in output file regulary).   

        */
        first_word = extract_first_word_dynamic(buffer);

        /* CASE 1: line starts with macro start label:   */

        if (strcmp(first_word, macro_start_label) == 0) {

            Macro * curr_macro;

            char * second_word = extract_second_word_dynamic(buffer); /*    second word is macro name (first word is macro start label) */

            /* EDGE CASE CHECK: if macro name occupied by command name (NOT VALID), if occupied - free everything and exit program: */

            if (check_if_macro_name_is_command(second_word, commands_arr, commands_arr_size) == 1)

            {

                printf("error! macro name is command name (macro '%s'). exit program\n", second_word);

                free(first_word);
                free(second_word);
				
		if(macro_head != NULL) {
                free_macro_list_with_lines(macro_head);
		}


                fclose(output_file); /* close output file */
                remove(file_name_with_format); /* delete output file */
                exit(1);

            }

            /* CREATE new macro node: */

            curr_macro = create_new_macro_node(second_word);

            free(second_word);

            /* SCAN lines to macro node till end label   */

            while (strcmp(first_word, macr_end_label) != 0) {
		
	

                fgets(buffer, sizeof(buffer), input_file);
                free(first_word);
                first_word = extract_first_word_dynamic(buffer);

                /* if first word of current line is not macro end label: */

                if (strcmp(first_word, macr_end_label) != 0) {

                    Line * new_line_node = create_new_line_node(buffer);
                    add_line_node_to_macro(curr_macro, new_line_node);

                }

            }

        
            add_macro_node_to_end( & macro_head, curr_macro);
        }

        /* CASE 2,3: line do not start with macro start label    */
        else {

            Macro * macro_ptr = serach_macro_in_list_by_name(macro_head, first_word); /*if first name is macro name*/

            /* CASE 2: first word is macro call  */

            if (macro_ptr != NULL) {

                write_opened_macro_to_file(output_file, macro_ptr);
            }

            /* CASE 3: first word is not macro related)  */
            else {
                fprintf(output_file, "%s", buffer);
            }

        }
        free(first_word);

    }

    /* FREE all allocated meamory of macro linked (including lines) */
	
	if(macro_head != NULL) {
    	free_macro_list_with_lines(macro_head);
	
	}
    /* CLOSE input and output file */

    fclose(input_file);
    fclose(output_file);

    /* RETURN pointer to the new output file: */

    return 0;

    /* END of macro proccess */

}

