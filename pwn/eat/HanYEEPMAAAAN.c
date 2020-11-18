#include <string.h>
#include <unistd.h>
#include <stdio.h>

//gcc -m32 -mpreferred-stack-boundary=2 -fno-stack-protector -no-pie -fno-pic -o test test.c

unsigned int init() {
	//system("/usr/bin/clear");
	setvbuf(stdout, 0, 2, 0);
  	setvbuf(stdin, 0, 2, 0);
  	setvbuf(stderr, 0, 2, 0);
	return alarm(0x1Fu);
}

void choice1(){
	puts("Im hungry...,,,.,,, Not Today");
}

void choice2(){
	puts("Good Bye!");
}

int main(){
	char choice[100];
	init();
	memset(choice, 0, 100);

	puts("I wanT P1ZZ@~~~!~!~!");
	puts("Han Yeep MAN?");
	puts("1. Yes 2. No");
	printf("Ur Choice : ");
	read(0, choice, 256);
	write(1, choice, 100);
	if(choice[0] == '1')
		choice1();
	else if(choice[0] == '2')
		choice2();
	return 0;
}
