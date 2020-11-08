//`p_{llfbkxs_rv
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char key[] = "amazing_mypass";
void encrypted(char *flag)
{
	int i = 0;
	for(i = 0; i < strlen(flag); i++){
		switch(i%3){
			case 1: flag[i] -= 3; break;
			case 2: flag[i] += 2; break;
			case 0: flag[i] ^= 1; break;
		}
	}
}

int main()
{
	char flag[30];
	memset(flag,0,sizeof(flag));
	printf("Input Key : ");
        scanf("%s",flag);	
	encrypted(flag);

	if(strcmp(flag,key)==0)
		printf("Correct\n");
	else
		printf("Incorrect\n");

}
