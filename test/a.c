#include <stdio.h>
#include <unistd.h>
int main(){
	
	int a=0x12345678;
	char b=0xaa;

	char buf[100];
printf("ret=%d\n", snprintf(buf,100,"%x:%04hhx\n", a,b) );
printf("%s\n",buf);


}



