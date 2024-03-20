#include "header.h"

void first_assembler(FILE* pfile){

	//int bin=dec_to_bin(20);
     	//printf("IN base 64 = %c\n",encoding_table[bin_to_base64(bin)]);
	
	//open file
	//FILE* pfile=fopen(file,"r+");
	//check_open_file(pfile);
	fseek(pfile,START_OF_LINE,SEEK_SET);//move to the begining of the file
	int line_amount=count_lines(pfile);
	fseek(pfile,START_OF_LINE,SEEK_SET);//move to the begining of the file
	FILE* p_ob_file=fopen("ps.ob","wt");
	check_open_file(p_ob_file);

	//definations for reading the file
	char* line;
	char* word;
	int num_line=0;
	int index_in_line;
	int IC;
	int DC;
	int error=FALSE;

	//definations for labels
	Label** labels=(Label**)malloc(sizeof(Label*));
	Label* lab;
	int labels_counter=0;
	int label_exists=FALSE;

	//definations for inst
	int num_inst;
	char* op=(char*)malloc(MAX_OPERAND*sizeof(char));
	check_allocation_charp(op);
	char* str=(char*)malloc(MAX_OPERAND*sizeof(char));
	check_allocation_charp(str);	

	int entry_exists=FALSE;
	int extern_exists=FALSE;	
	FILE* p_entry_file=fopen("ps.ent","wt");
	check_open_file(p_entry_file);
	FILE* p_extern_file=fopen("ps.ext","wt");
	check_open_file(p_extern_file);
	
	//definations for command
	int num_command;
	char* sor_op;
	char* des_op;
	int sor_op_add;
	int des_op_add;
	int sor_reg_num;
	int des_reg_num;

	//definations for output
	int* bin_inst_array=(int*)malloc(sizeof(int));
	check_allocation_intp(bin_inst_array);
	int* bin_data_array=(int*)malloc(sizeof(int));
	check_allocation_intp(bin_data_array);
	int bin_inst;
	int bin_data;
	
	IC=BASIC_ADDRESSING;
	//int line_amount=4;
	//read the givven file(after the mcros writing)
	
	while(num_line<line_amount){
		num_line++;
		index_in_line=0;
		line=(char*)malloc(MAX_LINE*sizeof(char));
		check_allocation_charp(line);
		word=(char*)malloc(MAX_WORD*sizeof(char));
		check_allocation_charp(word);	
		if(fgets(line,MAX_LINE,pfile)!= (char*)NULL){//get line
			index_in_line+=spaces_counter(line,index_in_line);
			word=get_word(line,index_in_line);
			printf("line is: %s\n",line);
			printf("num command is: %d\n",get_num_command(word));
			//check if there is a label
			if(defination_of_label(word)==TRUE){
				char* name_label=word_without_definition_label(word);
				if(word_is_label(name_label)==TRUE){
					label_exists=TRUE;
					if(labels_counter>0){
						labels=(Label**)realloc(labels,(labels_counter+1)*sizeof(Label*));
						if(labels==NULL){
							printf("allocatin falied\n");
							exit(1);}
						}
					//alocate new lab in labels[labels_counter]
					lab=(Label*)malloc(sizeof(Label));
					if(lab==NULL){
						printf("allocatin falied\n");
						exit(1);}
					//define lab
					lab->name=name_label;
					lab->add=IC;
					labels[labels_counter]=lab;
					printf("lab->name is: %s\n",(labels[labels_counter])->name);
					printf("lab->add is: %d\n",(labels[labels_counter])->add);
					labels_counter++;	
				}//end of ok labeles
				else{//there is dafination of label but illigal label
					error=TRUE;
					error_illigal_label(num_line);}
				index_in_line+=(strlen(word)+1);
				index_in_line+=spaces_counter(line,index_in_line);
				word=get_word(line,index_in_line);
			}//end of check label

			//check if it is inst 	
			if(get_inst(word)!=NOT_IDENTIFIED){
				num_inst=get_inst(word);
				printf("in line %d num inst is: %d\n",num_line,num_inst);
				index_in_line+=strlen(word);
				index_in_line+=spaces_counter(line,index_in_line);
		
				//the inst is .data
				if(num_inst == DATA){
					op=get_operand(line,index_in_line);
					while(if_not_empty_word(op)==TRUE){//the word is not empty
						if(word_is_num(op)==FALSE){//the operand is not num
							error=TRUE;
							error_expected_num(num_line);}
						//the op is num
						printf("bin is: %ld\n",dec_to_bin(atoi(op)));
						index_in_line+=strlen(op);
						index_in_line+=1;//+ the char ','
						index_in_line+=spaces_counter(line,index_in_line);
						op=get_operand(line,index_in_line);
					}//end of while read numbers from line	
				}//end of .data
				//if the inst is .string
				else if(num_inst == STRING){
					printf("in line %s index is: %d\n",line,index_in_line);
					str=get_word(line,index_in_line);
					printf("str is: %s\n",str);
					if(word_is_string(str)==FALSE){
						error=TRUE;
						error_expected_str(num_line);}
					bin_data = char_to_bin('a');
					//allocate place to the bin code 
					/*if(IC-BASIC_ADDRESSING>1){
						bin_inst_array=(char**)realloc(bin_inst_array,(IC-BASIC_ADDRESSING+1)*sizeof(char*));
						check_allocation_charpp(bin_inst_array);}
					bin_inst[IC-BASIC_ADDRESSING]=(char*)malloc(SIZE_BIN_CODE*sizeof(char));
					check_allocation_charp(bin_inst[IC-BASIC_ADDRESSING]);*/
					
				}//end of .string	
			}//end of check inst

			//check if it is legal command 
			else if(get_num_command(word)!=NOT_IDENTIFIED){
				num_command=get_num_command(word);
				printf("num command is: %d\n",num_command);
				index_in_line+=strlen(word);
				index_in_line+=spaces_counter(line,index_in_line);
				sor_op=get_operand(line,index_in_line);
				//check source operand
				if(num_command_need_sor_op(num_command)==FALSE){
					error=TRUE;
					error_command_not_consumed_sor_op(num_line);}
				else{//num command need the sor op
					if(if_not_empty_word(sor_op)==FALSE){//if the name of register empty
						error=TRUE;
						error_not_given_sor_op(num_line);}
					else{//command have sor op
						sor_op_add=operand_addressing(sor_op);
						//illigal operand- no addressing
						if(sor_op_add == NOT_IDENTIFIED){
							error=TRUE;
							error_illigal_operand(num_line);}
						//the command dont allow the found addressing
						else if(command_allow_sor_op_add(num_command,sor_op_add)==FALSE){
							error=TRUE;
							error_illigal_sor_op_addressing(num_line);}
						//the sor op is in direct addressing- the operand is register
						else if(sor_op_add == DIRECT_REGISTER_ADDRESSING){
							sor_reg_num=get_num_of_reg(sor_op);
							if(word_is_register(sor_op)==FALSE){//illigal name of register
								error=TRUE;
								error_unknown_register(num_line);}
							else if((legal_num_of_reg(sor_reg_num))==FALSE){//if the num of the register is not exists
								error=TRUE;
								error_illigal_num_of_reg(num_line);}
						//after this num of register is ok
						}//end of direct register addressing
						//if the sor op is in DIRECT_ADDRESSING- the operand is label
						else if(sor_op_add == DIRECT_ADDRESSING){
							//if the word is illigal label
							if(word_is_label(sor_op)==FALSE){
								error=TRUE;
								error_illigal_label(num_line);}
						}//end of direct addressing
						//if the sor op is in INSTANT_ADDRESSING- the operand is num
						else if(sor_op_add == INSTANT_ADDRESSING){
							//illigal number
							if(word_is_num(sor_op)==FALSE){
								error=TRUE;
								error_illigal_number(num_line);}
							else{//legal number
							printf("the bin value is: %ld\n",dec_to_bin(atoi(sor_op)));}
						}//end of instant addressing
					}//end of command have sor op
			}//end of get source operand?
				}//end of ligal command
		else{//unknown command
			error=TRUE;
			error_unknown_command(num_line);}
		}//end of get line
	}//end of while
	//printf("num command is: %d\n",num_command);
	printf("line amount is: %d\n",line_amount);


	//close files
	fclose(pfile);
	fclose(p_ob_file);
	fclose(p_entry_file);
	fclose(p_extern_file);

	//free allocations
	for(int i=0; i<labels_counter;i++)
		free(labels[i]);
	free(line);
	free(word);
	free(op);

	
}


