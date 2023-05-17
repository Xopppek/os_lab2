#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_ARGS 20
#define MAX_PROGS 10
#define MAX_ARG_LENGTH 20
#define MAX_PROG_LENGTH 50
#define INPUT_SIZE 1024 
int main(){ 
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

	token = strtok(input, " \n");
	bool is_name = true;
	while(token != NULL){
		if(strcmp(token, "|") == 0){
			is_name = true;
		}	
		else if(is_name){
			strcpy(programs[num_programs], token);
			num_programs++;
			strcpy(args[num_programs-1][num_args[num_programs-1]], token);
			num_args[num_programs-1]++;//first arg is prog name
			is_name = false;
		}else{
			strcpy(args[num_programs-1][num_args[num_programs-1]], token);
			num_args[num_programs-1]++;
		}
		token = strtok(NULL, " \n");
	}

	kill(getppid(), SIGUSR1);
	printf("B sent signal\n");
//=========Printing parsed info for testing=======//	
/*	printf("Names: ");
	for (i = 0; i < num_programs; i++)
		printf("%s, ", programs[i]);
	printf("\n");
	for (i = 0; i < num_programs; i++){
		printf("Arguments for %s: ", programs[i]);
		for (j = 0; j < num_args[i]; j++)
			printf("%s, ", args[i][j]);
		printf("\n");
	}*/
//============Creating child processes=============//
	pid_t pid;
	int num_pipes = num_programs * 2 + 2;
	int fd[num_pipes * 2];
	for(i = 0; i < num_pipes; i++){
		if(pipe(fd + 2 * i) < 0){
			perror("pipe error");
			exit(EXIT_FAILURE);
		}
	}

	for(i = 0; i < num_programs; i++){
		pid = fork();
		if(pid == 0){
			if (i != num_programs-1){
				if(dup2(fd[i * 2 + 1], STDOUT_FILENO) < 0){
					perror("dup2 OUTPUT error");
					exit(EXIT_FAILURE);
				}
			}

			if(i != 0){
				if(dup2(fd[i*2-2], STDIN_FILENO) < 0){
					perror("dup2 INPUT error");
					exit(EXIT_FAILURE);
				}
			}

			for(j=0; j < 2*num_pipes; j++)
				close(fd[j]);
			char* temp[num_args[i] + 1];
			for(j = 0; j < num_args[i]; j++)
				temp[j] = args[i][j];
			temp[num_args[i]] = NULL;
			if(execvp(programs[i], temp)){
				perror("execvp error");
				exit(EXIT_FAILURE);
			}
		}else if (pid < 0){
			perror("fork error");
			exit(EXIT_FAILURE);
		}
	}

	for(i = 0; i < 2 * num_pipes; i++)
		close(fd[i]);
	for(i = 0; i < num_programs; i++)
		wait(NULL);

	exit(EXIT_SUCCESS);
} 
