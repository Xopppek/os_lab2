#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int is_waiting = 1;

void signal_handler(int sig){
	printf("A got signal\n");
	is_waiting = 0;
}

int main(){
	int n = 3;
	signal(SIGUSR1, signal_handler);
	pid_t id = fork();
	if(id == 0){
		execl("./b", "program B",  NULL);
	}else if(id == -1){
		perror("fork error in A");
		exit(1);
	}
	printf("program A is waiting for signal\n");
	//pause();
	while (is_waiting)
		sleep(0);
	sleep(n);
	if (waitpid(id, NULL, WNOHANG) == 0){
		printf("Program B did not finish within %d seconds\nTeminating B and subprograms...\n", n);
		killpg(getpgid(id), SIGTERM);
		printf("B terminated\n");
	}	
		
	exit(0);
}
