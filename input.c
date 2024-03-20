#include "header.h"

//check if a file open
void check_open_file(FILE* pfile){
	if (pfile == NULL){
		printf("I can't open the file\n");
		exit(1);}
}

//check if dinamic allocation succeed
void check_allocation_charp(char* pointer){
	 if (pointer == NULL){
        	printf("allocation fall\n");
        	exit(1);}
}

void check_allocation_charpp(char** pointer){
	 if (pointer == NULL){
        	printf("allocation fall\n");
        	exit(1);}
}

void check_allocation_intp(int* pointer){
	 if (pointer == NULL){
        	printf("allocation fall\n");
        	exit(1);}
}


//count lines in a givven file
int count_lines(FILE* pfile){
	int line_count=0;
	char* line=(char*)malloc(MAX_LINE*sizeof(char));
	check_allocation_charp(line);
	while(fgets(line,MAX_LINE,pfile) != NULL) {
    		line_count++;	
  	}
	return line_count;
}

//count the spaces in a givven line in a givven index
int spaces_counter(char* line,int index_in_line){
	int i=0;
	while (line[index_in_line] ==' '){
		index_in_line++;
		i++;}
	return i;
}
//get line and the index after cutting spaces
char* get_word(char* line,int index_in_line){
	char* word;
	word=(char*)malloc(MAX_WORD*sizeof(char));
	check_allocation_charp(word);
	int i=0;				
	while(line[index_in_line] != '\n' && line[index_in_line] != '\0' && line[index_in_line]!= ' '){
		word[i]=line[index_in_line];
		//printf("word[i]= %c\n",word[i]);
		index_in_line++;
		i++;}
	word[i]='\0';//end of string
	//printf("in get word, word is: %s\n",word);	
	return word;		
}

//get line and the index after cutting spaces
char* get_word2(char* line,int index_in_line){
	char* word;
	int i=0;				
	while(line[index_in_line] != '\n' && line[index_in_line] != '\0' && line[index_in_line]!= ' '){
		word[i]=line[index_in_line];
		//printf("word[i]= %c\n",word[i]);
		index_in_line++;
		i++;}
	word[i]='\0';//end of string
	//printf("in get word, word is: %s\n",word);	
	return word;		
}

//return 1 if there is and 0 else
int check_if_there_is_unnecessary_word(char* line,int index_in_line){
	char* word =get_word(line,index_in_line);
		if(if_not_empty_word(word)==TRUE)
			return TRUE;
	return FALSE;
}

//check if to ignore the line return 1 not ignore and 0 to ignore
int if_not_ignore_line(char* line){
	int spaces=spaces_counter(line,START_OF_LINE);
	if(line[spaces]!='\n' && line[spaces]!=';')
		return 1;//not ignore
	else//ignore
		return 0;
}

int if_not_empty_word(char* word){
	int i=0;
	while(word[i]!='\0'){//if we still in the word
		if(word[i]!=' ' && word[i]!='\n')//if the char is a latter
			return 1;
		i++;}
	return 0;//if the word is empty
}

//check if word is lega string
int word_is_string(char* word){
	//string dont start in "	
	if(word[0]!= '"')
		return FALSE;
	//string dond end in "
	if(word[strlen(word)-1]!= '"')
		return FALSE;
	return TRUE;
}

//return true if the word is number and false else
int word_is_num(char* word){

	if(word[0]!='-' && word[0] !='+' && char_is_num(word[0])==FALSE)
		return FALSE;
	int i=1;
	while(word[i]!='\0'){
		if(char_is_num(word[i])==FALSE)
			return FALSE;
		i++;}
	return TRUE;
}
//return true if the char is number and false else
int char_is_num(char ch){
	if(ch=='0' || ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5' || ch=='6' || ch=='7' || ch=='8' || ch=='9')
		return TRUE;
	return FALSE;
}

//check if the char is lower latter
int check_lower_latter(char ch){
	if(ch >= 'a' && ch <= 'z')// if the latter is lower
		return 1;
	return 0;//if not lower latter
}

//check if the char is upper latter
int check_upper_latter(char ch){
	if(ch >= 'A' && ch <= 'Z')// if the latter is upper
		return 1;
	return 0;//if not upper latter
}

//check if the word is start of instruction.
int check_if_inst(char* word){
	if(word[0] == '.')
		return 1;
	return 0;
}

//check if the first word is mcro
int check_if_mcro(char* word){
	if(strcmp(word,"mcro")==0)
		return 1;
	return 0;
}

//check if the first word is end of mcro
int check_if_endmcro(char* word){
	if(strcmp(word,"endmcro")==0)
		return 1;
	return 0;
}	

//get array of pionters to char* and name of mcro, check if the name of mcro exists
int check_if_name_mcro_exists(char** mcros_names,char* mcro_name,int index_in_mcros_names){
	int i=0;
	//check if the name in the mcros array
	while(i<(index_in_mcros_names)){//i<amount of variables in mcros values
		if(strcmp(get_word(mcros_names[i],START_OF_LINE),mcro_name)==0){//if the first word in the array like the givven name of mcro
			return 1;}
		i++;}
	//else- when i didnt find the givven mcro name in the mcros table
	return 0;
}
//return the num of first txt line of the givven mcro (the mcro givven in word)
int num_of_first_txt_line_mcro(char** mcros_values,int index_in_mcros_values,char* word){
	int i=0;
	while(i<=(index_in_mcros_values)){//i<amount of variables in mcros values
		if(strcmp(get_word(mcros_values[i],START_OF_LINE),word)==0)//if the first word in the array like the givven name of mcro
			return i+1;
		i++;
	}
	return 0;//not happened because the function called after it checks that the mcro exists.
}
//return the num of last txt line of the givven mcro (the mcro givven in word)
int num_of_last_txt_line_mcro(char** mcros_values,int index_in_mcros_values,char** mcros_names,int index_in_mcros_names,char* word,int num_first_txt_line){
	int i=num_first_txt_line;
	while (i<index_in_mcros_values){
		if(check_if_name_mcro_exists(mcros_names,get_word(mcros_values[i],START_OF_LINE),index_in_mcros_names)==TRUE)
			return i-1;
		i++;
	}
	return i-1;//the last txt line of the mcro is the last string in mcros names
}

//check if the word is name of inst
int get_inst(char* word){
	if(strcmp(word,".data")==0)
		return DATA;
	else if(strcmp(word,".string")==0)
		return STRING;
	else if(strcmp(word,".extern")==0)
		return EXTERN;
	else if(strcmp(word,".entry")==0)
		return ENTRY;
	else//its not instrction
		return NOT_IDENTIFIED;
}

//get command and return the dec code of the command
int get_num_command(char* word){
	if(strcmp(word,"mov")==0)
		return MOV;
	if(strcmp(word,"cmp")==0)
		return CMP;
	if(strcmp(word,"add")==0)
		return ADD;
	if(strcmp(word,"sub")==0)
		return SUB;
	if(strcmp(word,"not")==0)
		return NOT;
	if(strcmp(word,"clr")==0)
		return CLR;
	if(strcmp(word,"lea")==0)
		return LEA;
	if(strcmp(word,"inc")==0)
		return INC;
	if(strcmp(word,"dec")==0)
		return DEC;
	if(strcmp(word,"jmp")==0)
		return JMP;
	if(strcmp(word,"bne")==0)
		return BNE;
	if(strcmp(word,"red")==0)
		return RED;
	if(strcmp(word,"prn")==0)
		return PRN;
	if(strcmp(word,"jsr")==0)
		return JSR;
	if(strcmp(word,"rts")==0)
		return RTS;
	if(strcmp(word,"stop")==0)
		return STOP;
	else
		return NOT_IDENTIFIED;	
}

//get line and the index after cutting spaces
char* get_operand(char* line,int index_in_line){
	char* operand;
	operand=(char*)malloc(MAX_OPERAND*sizeof(char));
	check_allocation_charp(operand);
	int i=0;				
	while(line[index_in_line] != '\n' && line[index_in_line] != '\0' && line[index_in_line]!= ' ' && line[index_in_line]!= ','){
		operand[i]=line[index_in_line];
		index_in_line++;
		i++;}
	operand[i]='\0';//end of string	
	return operand;		
}
//get operand and return the addressing
int operand_addressing(char* operand){
	if(operand[0]=='@')
		return DIRECT_REGISTER_ADDRESSING ;
	if(check_upper_latter(operand[0])==TRUE || check_lower_latter(operand[0])==TRUE)
		return DIRECT_ADDRESSING ;
	if(char_is_num(operand[0])==TRUE)
		return INSTANT_ADDRESSING ;

	else
		return NOT_IDENTIFIED ;
}
//check if the num of command allow the addressing that recognized 
int command_allow_sor_op_add(int num_command,int sor_op_add){
	if(num_command==LEA && sor_op_add!=DIRECT_ADDRESSING)
		return FALSE;
	else//the command need the addressing of sor op
		return TRUE;
}
//check if the num of command allow the addressing that recognized 
int command_allow_des_op_add(int num_command,int sor_op_add){
	//jmp and prn get all addressing
	if(num_command==JMP || num_command==PRN)
		return TRUE;
	//action that get des op and cant get INSTANT_ADDRESSING
	else if(sor_op_add != INSTANT_ADDRESSING)
		return TRUE;
	else
		return FALSE;
}

//return if the command need source operand
int num_command_need_sor_op(int num_command){

	if(num_command==MOV || num_command==CMP || num_command==ADD || num_command==SUB || num_command==LEA)
		return TRUE;//need source op
	return FALSE;//dond need source op
}

//return if the command need destination operand
int num_command_need_des_op(int num_command){

	if(num_command!=RTS && num_command!=STOP)
		return TRUE;//need destination op
	return FALSE;//dond need destination op
}
//return if a word is register
int word_is_register(char* reg){
	int i=0;
	//if not enough chars in reg name
	if(strlen(reg)<3)
		return FALSE;
	//if it is ligal name of reg
	if(reg[0]=='@' && reg[1]=='r' && char_is_num(reg[2])==TRUE)
		return TRUE;
	//itsnt ligal name of reg
	return FALSE;
}

//return the number of register
int get_num_of_reg(char* reg){
	
	char* num_of_reg=(char*)malloc(MAX_NUM_OF_REG *sizeof(char));
	check_allocation_charp(num_of_reg);	
	int i=2;
	int j=0;
	while(reg[i]!='\0'){
		num_of_reg[j]=reg[i];
		i++;
		j++;}

	//return the number of the register
	return atoi(num_of_reg);
}

//return true if the number is legal
int legal_num_of_reg(int num){
	if(num>=MIN_NUM_REG && num<=MAX_NUM_REG)
		return TRUE;
	return FALSE;
}

//check if a word is label
int word_is_label(char* word){
	
	//label cant start in somthing else latter
	if(check_upper_latter(word[0])==FALSE && check_lower_latter(word[0])==FALSE)
		return FALSE;
	int i=1;
	//check every latter in word to check if it is legal label
	while(word[i]!='\0'){
		if(check_upper_latter(word[i])==FALSE && check_lower_latter(word[i])==FALSE && char_is_num(word[i])==FALSE)
			return FALSE;
		i++;}
	return TRUE;	
}
//check if there is difination of label
int defination_of_label(char* word){
	if(word[strlen(word)-1]==':')
		return TRUE;
	else
		return FALSE;
}

//check if word is definition of label
char* word_without_definition_label(char* word){
		word[strlen(word)-1]='\0';
		return word;
}

//check if label already exists in the labels table
/*int label_already_exists(Label* labels){


}*/


