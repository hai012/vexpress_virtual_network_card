#include<stdio.h>
#include <string.h>
char b='\377';


int main()
{
printf("%d,%d\n",sizeof(b),sizeof('\377'));
printf("%x\n",b);
	return 0;
}
