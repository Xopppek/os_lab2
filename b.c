#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define MAX_ARGS 20
#define MAX_PROGS 10
#define MAX_ARG_LENGTH 20
#define MAX_PROG_LENGTH 50
#define INPUT_SIZE 1024 
int main(){ 
/*	char input[100];
	fgets(input, 100, stdin);
	kill(getppid(), SIGUSR1);
	printf("b sent signal to %d\n", getppid());
	system(input);*/
	
	char input[INPUT_SIZE];
	char args[MAX_PROGS][MAX_ARGS][MAX_ARG_LENGTH];
	char programs[MAX_PROGS][MAX_PROG_LENGTH];
	char* token;

	printf("Program B is waiting for input:\n");
	fgets(input, INPUT_SIZE, stdin);

//=================Parsing================//

	int num_programs = 0;
	int num_args[MAX_PROGS] = {0};
	int i = 0, j = 0;

	token = strtok(input, " ");
	int is_name = 1;
	while(token != NULL){
		if(strcmp(token, "|") == 0){
			is_name = 1;
		}	
		else if(is_name == 1){
			strcpy(programs[num_programs], token);
			num_programs++;
			is_name = 0;
		}else{
			strcpy(args[num_programs-1][num_args[num_programs-1]], token);
			num_args[num_programs-1]++;
		}
		token = strtok(NULL, " \n");
	}
//=========Printing parsed info for testing=======//	
	printf("Names: ");
	for (i = 0; i < num_programs; i++)
		printf("%s, ", programs[i]);
	printf("\n");

	for (i = 0; i < num_programs; i++){
		printf("Arguments for %s: ", programs[i]);
		for (j = 0; j < num_args[i]; j++)
			printf("%s, ", args[i][j]);
		printf("\n");
	}
	

	exit(0);
} 
