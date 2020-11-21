#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//gcc -o ez_pwn ez_pwn.c -m32 -fstack-protector -z norelro -no-pie -mpreferred-stack-boundary=2
int guest_Book(){
    char buf[50] = {0, };
    char comant[50] = {0, };

    printf("Write Guest Book\n");
    write(1, "What is your Name : ", 21);
    read(0, buf, 0x100);
    puts(buf);
    write(1, "What is your Comant : ", 23);
    read(0, comant, 0x100);
    puts(comant);

    return 0;
}

int game(){
    int i, c, cnt = 0;
    int n1, n2;
    printf("Play Baskin Robbins Game\n");

    while (1){
        if(cnt >= 31)
            break;
        else{
            printf("Enter one of the numbers from 1 to 3.\n");
            scanf("%1d", &n1);
            c = cnt;
            for(i = c +1; i <= (n1+c); i++){
                printf("%1d ", i);
                cnt++;
            }
	    printf("\n");

            if(cnt == 31){
                printf("You are winner!!!\n");
                break;
            }
            c = cnt;
            srand(time(NULL));
            n2 = rand() % 3+1;
            printf("my program : %1d\n", n2);

            for(i = c+1; i <= (n2+c); i++){
                printf("%1d ", i);
                cnt++;
            }
	    printf("\n");

            if(cnt == 31){
                printf("You are loser!!!\n");
                break;
            }
        }
    }
    return 0;
}

int main(){
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    int sel;
    
    while(1){
    	printf("###Welcome My Program###\n");
    	printf("1. Write Guest Book\n");
    	printf("2. Play Game\n");
    	printf("3. Bye~~\n");
    	scanf("%d", &sel);
    
    	switch(sel){
        	case 1:
            		guest_Book();
            		break;
        	case 2:
            		game();
            		break;
        	case 3:
            		puts("Good Bye!!!");
            		exit(0);
        	default:
            		exit(0);
            	break;
    	}
    }
    return 0;
}
