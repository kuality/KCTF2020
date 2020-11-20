#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>

double master_key;
char name[100];
int guest_key=1;
int suppppper_key=2;
void (*hello)();

unsigned int init() {
	unsigned char buffer;
	int f = open("dev/urandom", O_RDONLY);
	read(f, &buffer, 1);
	srand(buffer);
	system("/usr/bin/clear");
	setvbuf(stdout, 0, 2, 0);
	setvbuf(stdin, 0, 2, 0);
	setvbuf(stderr, 0, 2, 0);
	memset(name, 0, 0x64);
	master_key = rand();
	return alarm(0x10u);
}
void press(){
	__asm(
//		"push %ebp;"
		"mov %ebx, %ecx;"
		"mov %eax, %edx;"
		"push %edx;"
		"add %eax, 0x100;"
		"nop;"
		"push %ebp;"
		"push %ebx;"
		"mov %eax, %ebp;"
		"sub %esp, 0x20;"
		"add %ebp, 0x10;"
		"add %ebx, 0x100;"

	);
}
int get_point() {
	char name1[100] = {};
	int num = 0, point;
	printf("당신의 이름은 무엇입니까?(input name only english)\n");
	point = read(0, &name1, 0x64);
	strcpy(name, name1);
	printf("%s님, 당신 이름의 점수는!!!\n", name);
//	sleep(0.5);
	if (point == 0)
	{
		printf("오류!오류!오류!");
		exit(1);
	}
	printf("%d점입니다!!\n", point % 100);
	if (point % 100 == 50) {
		printf("반이라도 가는 당신!! 훌륭하군요?!?!\n");
		return point%100;
	}
	else if (0 < (point % 100)) {
		if ((point % 100) < 50)
			printf("실망할건 없어요 그저 제가 더 훌륭할 뿐인걸요?!?\n");
		else
			printf("이보다 더 훌륭한 이름은 들어보지 못했어요...\n");
		return point%100;
	}
	else {
		printf("100점이라고요? 거짓말치지 말아요... 당신의 진짜 이름을 알려주세요!!!\n");
		return point%100;
	}
}
void comment() {
	printf("1. get_point\n");
	printf("2. lucky_chance!\n");
	printf("3. 열려라 참깨~!\n");
	printf("4. 권한얻기!\n");
}
void call();
int have_auth(int point) {
	char a='y';
	read(0, &a, 1);
	if (a == 'y' || a == 'Y')
	{	
		if (point >= 999999999)
		{
			return master_key;
		}
		else if (point >= 10)
		{
			return suppppper_key;
		}
		else if (point >= 1)
			return guest_key;
		hello = &call;
		
	}
	(*hello)();
}
int lucky_chance() {
	printf("choose one number\n");
	int lucky = 0;
	scanf("%d", &lucky);
	if (lucky == rand())
	{
		printf("Congratuation!!\n");
		return 999999999;
	}
	__asm(
			"NOP;"
	     );
	
}
void win() {
        printf("Can you get a key?");
        system("/bin/sh");
}

void call() {
        printf("%s님, 방문을 환영합니다.\n", name);
}

void open_door(int a) {
	if (a == master_key)
		win();
}
int main() {
	init();
	
	int i = 0;
	int num = 0;
	int auth;
	int point = 0; 

	while(1){
		comment();
		scanf("%d", &num);
		
		if (num == 1)
		{
			point += get_point(); // 여기서 point 지정
		}
		else if (num == 2)
		{
			point += lucky_chance();
		}
		else if (num == 3)
		{
			open_door(point);
		}
		else if (num == 4) {
			have_auth(point);
		}
		else
			exit(1);
		
	}

	return 0;
}
