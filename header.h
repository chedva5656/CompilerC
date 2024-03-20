//standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//macros
#define TRUE 1
#define FALSE 0
//input mcros
#define MAX_LINE 80
#define MAX_WORD 15
#define START_OF_LINE 0
//pre assembler mcros
#define MAX_MCRO 15
#define CHARS_OF_MCRO 4
#define CHARS_OF_ENDMCRO 7
//first assembler mcros
#define SIZE_BIN_CODE 13
#define SIZE_BACK_SLESH_ZERO 1
#define BASIC_ADDRESSING 100
#define MAX_OPERAND 31
#define MAX_STRING 31
#define DIRECT_REGISTER_ADDRESSING 5
#define DIRECT_ADDRESSING 3
#define INSTANT_ADDRESSING 1
#define MIN_NUM_REG 0
#define MAX_NUM_REG 7
#define MAX_NUM_OF_REG 10
//returned values from functions
#define NOT_IDENTIFIED -1
#define DATA 1
#define STRING 2
#define EXTERN 3
#define ENTRY 4

#define MOV 0
#define CMP 1
#define ADD 2
#define SUB 3
#define NOT 4
#define CLR 5
#define LEA 6
#define INC 7
#define DEC 8
#define JMP 9
#define BNE 10
#define RED 11
#define PRN 12
#define JSR 13
#define RTS 14
#define STOP 15

//defitions of types
typedef struct Label{
	char* name;
	int add;
	char* type;
}Label;

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'}; 

//functions in main.c
void assembler(char* file);

//functions in preass.c
FILE* pre_assembler(char* file);

//functions in firstass.c
void first_assembler(FILE* file);

//functions in input.c
void check_open_file(FILE* pfile);
void check_allocation_charp(char* pointer);
void check_allocation_charpp(char** pointer);
void check_allocation_intp(int* pointer);
int count_lines(FILE* pfile);
int spaces_counter(char* line,int index_in_line);
char* get_word(char* line,int index_in_line);
char* get_word2(char* line,int index_in_line);
int check_if_there_is_unnecessary_word(char* line,int index_in_line);
int if_not_ignore_line(char* line);
int if_not_empty_word(char* word);
int word_is_string(char* word);
int word_is_num(char* word);
int char_is_num(char ch);
int check_lower_latter(char ch);
int check_upper_latter(char ch);
int check_if_inst(char* word);
int check_if_mcro(char* word);
int check_if_endmcro(char* word);
int check_if_name_mcro_exists(char** mcros_names,char* mcro_name,int index_in_mcros_names);
int num_of_first_txt_line_mcro(char** mcros_values,int index_in_mcros_values,char* word);
int num_of_last_txt_line_mcro(char** mcros_values,int index_in_mcros_values,char** mcros_names,int index_in_mcros_names,char* word,int num_first_txt_line);
int get_inst(char* word);
int get_num_command(char* word);
char* get_operand(char* line,int index_in_line);
int operand_addressing(char* operand);
int command_allow_sor_op_add(int num_command,int sor_op_add);
int command_allow_des_op_add(int num_command,int sor_op_add);
int num_command_need_sor_op(int num_command);
int num_command_need_des_op(int num_command);
int word_is_register(char* reg);
int get_num_of_reg(char* reg);
int legal_num_of_reg(int num);
int word_is_label(char* word);
int defination_of_label(char* word);
char* word_without_definition_label(char* word);

//functions in output.c
long char_to_bin(char ch);
int power(int num,int p);
long dec_to_bin(int dec);
int bin_to_base64(int n);

//functions in error.c
void check_if_error_detected(int error);
void error_value_not_consumed(int num_line);
void error_unknown_command(int num_line);
void error_expected_num(int num_line);
void error_expected_str(int num_line);
void error_illigal_operand(int num_line);
void error_illigal_number(int num_line);
void error_command_not_consumed_sor_op(int num_line);
void error_command_not_consumed_des_op(int num_line);
void error_not_given_sor_op(int num_line);
void error_not_given_des_op(int num_line);
void error_illigal_sor_op_addressing(int num_line);
void error_illigal_des_op_addressing(int num_line);
void error_unknown_register(int num_line);
void error_illigal_num_of_reg(int num_line);
void error_illigal_label(int num_line);
void error_many_names_mcro(int num_line);
void error_no_name_mcro(int num_line);
void error_illegal_name_of_mcro(int num_line);
void error_mcro_name_already_exists(int num_line);
