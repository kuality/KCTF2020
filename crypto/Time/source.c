//KCTF{you'll_kn0w_that_life_is_Timing}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char input[101];
char flag[11] = "lxnfialzbd"; //no guessing 
int sleep_time = 1;

int check(char *flag, char *input) {
	int count = 0;
	if (strlen(input) <= strlen(flag)) {
		for (int i = 0; i < strlen(input);  i++) {
			if (flag[i] != input[i]){
				sleep(sleep_time);
				count++;
			}	
		}
	}
	else if (strlen(input) > strlen(flag)) {
		for (int i = 0; i < strlen(flag); i++) {
			if (flag[i] != input[i]) {
				sleep(sleep_time);
				count++;
			}
		}
		for (int i = strlen(flag) + 1; i < strlen(input); i++)
			input[i] = NULL;
	}
	
	if (count == 0)
		return 0;
	else
		return 1;
}

unsigned int init() {
	system("/usr/bin/clear");
	setvbuf(stdout, 0, 2, 0);
  	setvbuf(stdin, 0, 2, 0);
  	setvbuf(stderr, 0, 2, 0);
	return alarm(0x1Fu);
}

int main(void) {
	init();
	memset(input, 0, 0x65);
	int ver = 0;
	int cec = 0;

	puts("INPUT PASSCODE");

	do {
	
		read(0, input, 0x65u);
		if (strlen(input) == 0) {
			puts("input error");
			exit(1);
		}

		if (check(flag, input) == 1)
			puts("try again");

		else if (check(flag, input) == 0) {
			puts("well done ^^");
			system("cat flag");
			ver = 1;
		}
	} while (ver == 0);
}
	
