#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
int main(){
	char input[100];
	fgets(input, 100, stdin);
	kill(getppid(), SIGUSR1);
	printf("b sent signal to %d\n", getppid());
	system(input);
	exit(0);
} 
