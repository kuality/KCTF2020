#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//gcc -m32 -mpreferred-stack-boundary=2 -z execstack -no-pie -fno-stack-protector -o potato potato.c

unsigned int init() {
	setvbuf(stdout, 0, 2, 0);
	setvbuf(stdin, 0, 2, 0);
	setvbuf(stderr, 0, 2, 0);
	return alarm(0x1Fu);
}

void talk(){
	int amount;
	char drink[20];
	puts("I like to drink! What kind of drink do you like?");
	scanf("%s", drink);
	printf("So you like %s!\n", drink);
	puts("How much would you like to drink?");
	scanf("%d", amount);
	puts("Thanks for talking with me!");
}

int win(){
	printf("hey u know how to got overwrite!\n");
	return system("cat flag");
}

int main(){
	init();
	puts("Hello I am a talking potato");
	puts("Talk with me!");
	talk();
	return 0;
}
