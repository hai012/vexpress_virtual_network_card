#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig(int signo)
{
	printf("deal %d\n",signo);
}

int main(){

short a=32767;

signal(SIGFPE,sig);
printf("main %d\n", a/0);
printf("main %d\n", ++a);
while(1);

}



