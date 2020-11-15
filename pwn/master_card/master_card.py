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
int (*hello)();

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
	srand((unsigned int)time(0));
	master_key = rand();
	return alarm(0x1fu);
}

int get_point() {
	char name1[100] = {};
	int num = 0;
	printf("당신의 이름은 무엇입니까?(input name only english)\n");
	read(0, &name1, 0x64);
	strcpy(name, name1);
	printf("%s님, 당신 이름의 점수는!!!\n", name);
	for (int i = 0; i < (strlen(name)); i++)
	{
		//name[i%strlen(name)] ^= i;
		num += (int)(name[i]);
	}
	if (num == 0)
	{
		printf("오류!오류!오류!");
		exit(1);
	}
	printf("%d점입니다!!\n", num % 100);
	if (num % 100 == 50) {
		printf("반이라도 가는 당신!! 훌륭하군요?!?!\n");
		return num%100;
	}
	else if (0 < (num % 100)) {
		if ((num % 100) < 50)
			printf("실망할건 없어요 그저 제가 더 훌륭할 뿐인걸요?!?\n");
		else
			printf("이보다 더 훌륭한 이름은 들어보지 못했어요...\n");
		return num%100;
	}
	else {
		printf("100점이라고요? 거짓말치지 말아요... 당신의 진짜 이름을 알려주세요!!!\n");
		return num%100;
	}
}
void comment() {
	printf("1. get_point\n");
	printf("2. lucky_chance!\n");
	printf("3. 열려라 참깨~!\n");
	printf("4. 권한얻기!\n");
}
int call();
int have_auth(int point) {
	char a;
	scanf("%c", &a);
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
			"NOP;"
			"NOP;"
			"NOP;"
			"NOP;"
			"NOP;"
			"NOP;"
			"NOP;"
	     );
	
}
void win() {
        printf("Can you get a key?");
        system("/bin/sh");
}

int call() {
        if (name[0] == '\x00')
        {
                printf("초대받지 못한 손님입니다.\n");
                exit(1);
        }
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
	double point; //card == key값임

	while(1){
		comment();
		scanf("%d", &num);
		
		if (num == 1)
		{
			point = get_point(); // 여기서 point 지정
		}
		else if (num == 2)
		{
			point = lucky_chance();
		}
		else if (num == 3)
		{
			open_door(point);
		}
		else if (num == 4) {
			have_auth(auth);
		}
		else
			exit(1);
		
	}

	return 0;
}
