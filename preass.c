#include "header.h"

FILE* pre_assembler(char* file){

	//open .as file
	FILE* pfile=fopen(file,"rt");
	check_open_file(pfile);
	int line_amount=count_lines(pfile);
	fseek(pfile,START_OF_LINE,SEEK_SET);//move to the begining of the file

	int num_line=0;
	int index_in_line;
	int index_in_mcros_values=0;
	int index_in_mcros_names=0;
	int in_mcro=FALSE;
	int error=FALSE;
	char* line;
	char* word;
	char** mcros_values=(char**)malloc(sizeof(char*));
	check_allocation_charpp(mcros_values);
	char* mcro_name;
	char** mcros_names=(char**)malloc(sizeof(char*));
	check_allocation_charpp(mcros_names);
	//read the source file and save the macros
	while(num_line<line_amount){
		num_line++;
		index_in_line=0;
		line=(char*)malloc(MAX_LINE*sizeof(char));
		check_allocation_charp(line);	
		if(fgets(line,MAX_LINE,pfile)!= (char*)NULL)//get line
			if(if_not_ignore_line(line)==TRUE){//if it line to read
				//printf("line %d is: %s",num_line,line);
				index_in_line+=spaces_counter(line,index_in_line);
				word=get_word(line,index_in_line);
				//printf("word is: %s\n",word);
				index_in_line+=strlen(word);
				index_in_line+=spaces_counter(line,index_in_line);
				//printf("index in line is: %d\n",index_in_line);

				//if find end mcro
				if(check_if_endmcro(word)==TRUE && in_mcro==TRUE){
					in_mcro=FALSE;
					//check if there is unnecessary word after endmcro
					if(check_if_there_is_unnecessary_word(line,index_in_line)==TRUE){
						error=TRUE;
						error_value_not_consumed(num_line);}
				}//end of check endmcro
				
				//if in mcro, save the line
				else if(in_mcro==TRUE){
					mcros_values=(char**)realloc(mcros_values,(index_in_mcros_values+1)*sizeof(char*));
					check_allocation_charpp(mcros_values);
					mcros_values[index_in_mcros_values]=(char*)malloc(MAX_MCRO*sizeof(char));
					check_allocation_charp(mcros_values[index_in_mcros_values]);
					mcros_values[index_in_mcros_values]=line;
					index_in_mcros_values++;
				}//end of in mcro

				//if find mcro
				else if(check_if_mcro(word)==TRUE){
					in_mcro=TRUE;
					//get mcro name
					mcro_name=(char*)malloc(MAX_MCRO*sizeof(char));
					check_allocation_charp(mcro_name);
					mcro_name =get_word(line,index_in_line);
					//check if mcro name is empty
					if(if_not_empty_word(mcro_name)==FALSE){
						error=TRUE;
						error_no_name_mcro(num_line);}
					//if mcro name is inst or command
					else if(get_inst(mcro_name)!=NOT_IDENTIFIED || get_num_command(mcro_name)!=NOT_IDENTIFIED){
						error=TRUE;
						error_illegal_name_of_mcro(num_line);}
					//if name of mcro already exists
					else if(check_if_name_mcro_exists(mcros_names,mcro_name,index_in_mcros_names)==TRUE){
						error=TRUE;
						error_mcro_name_already_exists(num_line);}
					//if mcro ok
					else{
						//save the mcro name in mcros names
						if(index_in_mcros_names>0){
							mcros_names=(char**)realloc(mcros_names,(index_in_mcros_names+1)*sizeof(char*));
							check_allocation_charpp(mcros_names);}
						mcros_names[index_in_mcros_names]=(char*)malloc(MAX_MCRO*sizeof(char));
						check_allocation_charp(mcros_names[index_in_mcros_names]);
						mcros_names[index_in_mcros_names]=mcro_name;
						index_in_mcros_names++;
						//save the mcro name in mcros values
						if(index_in_mcros_values>0){
							mcros_values=(char**)realloc(mcros_values,(index_in_mcros_values+1)*sizeof(char*));
							check_allocation_charpp(mcros_values);}
						mcros_values[index_in_mcros_values]=(char*)malloc(MAX_MCRO*sizeof(char));
						check_allocation_charp(mcros_values[index_in_mcros_values]);
						mcros_values[index_in_mcros_values]=mcro_name;
						index_in_mcros_values++;
						//if there is a word after mcro name
						index_in_line+=strlen(mcro_name);
						index_in_line+=spaces_counter(line,index_in_line);
						if(check_if_there_is_unnecessary_word(line,index_in_line)==TRUE){
						error=TRUE;
						error_value_not_consumed(num_line);}
					}//end of mcro ok	
				}//end of check mcro	
			}//end line to read
	}//end of while

	//check if there is errors in the program
	check_if_error_detected(error);

	//print mcros values
	/*for(int i=0;i<index_in_mcros_values;i++)
		printf("in index %d in mcros values the string is: %s\n",i,mcros_values[i]);
	//print mcros names
	for(int i=0;i<index_in_mcros_names;i++)
		printf("in index %d in mcros names the string is: %s\n",i,mcros_names[i]);*/

	//no errors, write the ps file with writing the mcros inside 
	//open pre_assembler file.
	FILE* pfile_ps = fopen("ps.txt","w+");
	check_open_file(pfile_ps);
	
	fseek(pfile,START_OF_LINE,SEEK_SET);//move to the begining of the file

	num_line=0;
	int i;
	while(num_line<line_amount){
		num_line++;
		index_in_line=0;
		line=(char*)malloc(MAX_LINE*sizeof(char));
		check_allocation_charp(line);
		if(fgets(line,MAX_LINE,pfile)!= (char*)EOF)
			if(if_not_ignore_line(line)==TRUE){//not ignore line

				//printf("line %d is: %s",num_line,line);
				index_in_line+=spaces_counter(line,index_in_line);
				word=get_word(line,index_in_line);
				//printf("word is: %s\n",word);
				
				//if line with mcro
				if(check_if_mcro(word)==TRUE)	
					in_mcro=TRUE;
				//if line is endmcro
				else if(check_if_endmcro(word)==TRUE)
					in_mcro=FALSE;
				//if we find name of mcro in the source code
				else if(check_if_name_mcro_exists(mcros_names,word,index_in_mcros_names)==TRUE){
					int num_first_txt_line=num_of_first_txt_line_mcro(mcros_values,index_in_mcros_values,word);
					int num_last_txt_line=num_of_last_txt_line_mcro(mcros_values,index_in_mcros_values,mcros_names,index_in_mcros_names,word,num_first_txt_line);
					for(i=num_first_txt_line;i<=num_last_txt_line;i++)	
						fprintf(pfile_ps,"%s",mcros_values[i]);}
				//copy the line fron the source file to ps file
				else if(in_mcro==FALSE)
					fprintf(pfile_ps,"%s",line);
				
			}//end not ignore line
	}//end of while

	printf("The pre-assembler phase passed successfully\n");

	//close files
	fclose(pfile);
	//fclose(pfile_ps);

	//free allocations
	for(int i=0; i<index_in_mcros_values;i++)
		free(mcros_values[i]);
	for(int i=0; i<index_in_mcros_names;i++)
		free(mcros_names[i]);
	
	free(line);
	free(word);
	free(mcro_name);

	return pfile_ps;

}

