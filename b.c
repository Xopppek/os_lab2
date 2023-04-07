#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int b(){
	char input[100];
	fgets(input, 100, stdin);
	system(input);
	return 0;
} 
