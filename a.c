#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int flag = 0;

void signal_handler(int sig){
	flag = 1;
}

int main(){
	int n = 3;
	signal(SIGUSR1, signal_handler);
/*	sigset_t signal_mask;
	sigemptyset(&signal_mask);
	sigaddset(&signal_mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &signal_mask, NULL);*/

	pid_t id = fork();
	if(id == 0){
		execl("./b", "program B",  NULL);
	}
	else{
//		kill(id, SIGUSR1);
		printf("program A is waiting for signal\n");
		while (!flag){
			sleep(1);
		}
		printf("got signal\n");
		sleep(n);
	//	kill(id, SIGTERM);
		pid_t child_pid;
/*		do {
			child_pid = waitpid(-1, NULL, WNOHANG);
			if(child_pid > 0){
				kill(child_pid, SIGTERM);
			}
		} while (child_pid != 0);i*/
		printf("prigram b stopped\n");	
//		wait(NULL);
	//	printf("%d\n", getpid());
	}
	
	return 0;
}
