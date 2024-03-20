#include "header.h"

//read the code line by line
void assembler(char* file)
{
	FILE* ps_file;
	ps_file=pre_assembler(file);
	first_assembler(ps_file);
	
}


void main(int argc, char** argv)
{
	int i;
	for(i = 1; i < argc; i++){
		printf("file %s:\n",argv[i]);
		assembler(argv[i]);}	
}
