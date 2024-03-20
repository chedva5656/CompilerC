#include "header.h"
//error classic
void check_if_error_detected(int error){
	if(error==TRUE){
		printf("Sorry! errors detected, coming out of the program.\n");
		exit(1);}
}

//error commands
void error_value_not_consumed(int num_line){
	printf("Line %d: value not consumed\n",num_line);
}

void error_unknown_command(int num_line){
	printf("Line %d: unknown command\n",num_line);
}

//error inst
void error_expected_num(int num_line){
	printf("Line %d: expected number\n",num_line);
}

void error_expected_str(int num_line){
	printf("Line %d: expected legal string\n",num_line);
}

//error operands
void error_illigal_operand(int num_line){
	printf("Line %d: illigal operand\n",num_line);
}

void error_illigal_number(int num_line){
	printf("Line %d: illigal number\n",num_line);
}

//error registers
void error_command_not_consumed_sor_op(int num_line){
	printf("Line %d: source operand not consumed\n",num_line);
}

void error_command_not_consumed_des_op(int num_line){
	printf("Line %d: destination operand not consumed\n",num_line);
}

void error_not_given_sor_op(int num_line){
	printf("Line %d: not given source operand\n",num_line);
}

void error_not_given_des_op(int num_line){
	printf("Line %d: not given destination operand\n",num_line);
}

void error_illigal_sor_op_addressing(int num_line){
	printf("Line %d: the addressing method of the source operand is illigal\n",num_line);
}

void error_illigal_des_op_addressing(int num_line){
	printf("Line %d: the addressing method of the destination operand is illigal\n",num_line);
}

void error_unknown_register(int num_line){
	printf("Line %d: unknown name of register\n",num_line);
}

void error_illigal_num_of_reg(int num_line){
	printf("Line %d: illigal number of register\n",num_line);
}

//error labels
void error_illigal_label(int num_line){
	printf("Line %d: illigal label\n",num_line);
}

//error mcro
void error_many_names_mcro(int num_line){
	printf("Line %d: too much names for a mcro\n",num_line);
}

void error_no_name_mcro(int num_line){
	printf("Line %d: expected name for the mcro\n",num_line);
}

void error_illegal_name_of_mcro(int num_line){
	printf("Line %d: illegal name of the mcro\n",num_line);
}

void error_mcro_name_already_exists(int num_line){
	printf("Line %d: name of mcro already exists\n",num_line);
}
