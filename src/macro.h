#define LINE_MAX_LEN_WITH_NULL_TERMINATOR 80+1

/*  struct Line for linked list  */
typedef struct Line {
    char* line_content;
    struct Line* next;
} Line;

/*  struct Macro for linked list   */
typedef struct Macro {
    char* name;
    Line* macro_line_list;
    struct Macro* next;
} Macro;

int proccess_macro_file(char * file_name);

    /*  Line linked list functions   */
Line* create_new_line_node(char* input_line);
int add_line_node_to_macro(Macro* macro_node, Line* new_line_node);

/*  Macro linked list functions:  */
Macro* create_new_macro_node(char* name);
int add_macro_node_to_end(Macro** head, Macro* new_macro_node);

/*  Macro Functions:  */
int check_if_macro_name_is_command(char* word, char* commands_arr[], int size);
Macro* serach_macro_in_list_by_name(Macro* head, char* macro_name);

/*  output file functions:  */
int write_opened_macro_to_file(FILE* output_file, Macro* macro_node);

/*  free memory functions   */
int free_macro_list_with_lines(Macro* macro_head);
int free_Line_List(Line* head);

