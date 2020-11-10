#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//gcc -m32 -fno-stack-protector -z now -no-pie -fno-pic monster.c -o monster

char s[100];


int lose1(){
	puts("Well, the electric rat is smarter than you think.");
	puts("Now you got yourself killed as well as the villagers.");
	puts("How terrible is that. Try again");
}

int lose2(){
	puts("Wow, you tripped yourself while running.");
	puts("The electric rat gave you a warm electric shock. Try again");
}

int win(){
	char *argv;

	puts("Ooooh, nice job!");
	argv = "/bin/cat flag";
	return execve("/bin/cat flag", &argv, 0);
}

int village(){

	puts("\nNow, Should I....");
	puts("1. get into a house");
	puts("2. run to the city hall\n\n"); 

	fgets(s, 50, stdin);
	printf("You have chosen : ");
	printf(s);

	if(s[0] == '1')
		lose1();
	else if(s[0] == '2')
		lose2();

	return 0;		
}

int river(){
	puts("\n\nDon't you know that water is vulnerable to electricity?");
	puts("Thunderbolt was very effective! Try again.");
}

unsigned int init() {
	//system("/usr/bin/clear");
	setvbuf(stdout, 0, 2, 0);
  	setvbuf(stdin, 0, 2, 0);
  	setvbuf(stderr, 0, 2, 0);
	memset(s, 0, 0x40);
	//return alarm(0x200u);
	return 0;
}

int main(){
	init();

	puts("ELECTRIC RAT MONSTER is coming!");
	puts("choose between");
	puts("1. To the village");
	puts("2. To the river");
	puts("QUICK!!!!");
	puts("　   ▼￣＞-―-＜￣▼");
	puts("　　Ｙ　。  。  Ｙ");
	puts("/＼,/ 　● Å ●    ）");
	puts("＼ ｜　 つ　 ヽつ\n\n");

	for(int i=0;i<2;i++){	
	printf("Your Choice? :");
	fgets(s, 100, stdin);
	printf("You have chosen : ");
	printf(s);
	printf("%s", s);

	printf("Hmm....\n\n");
	if(s[0] == '1')
		village();
	else if(s[0] == '2')
		river();
	}
		
	return 0;
}



