#include <stdio.h>
#include <stdlib.h>
char *use_chuck;
char *chuck[10];
void init(){
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}
void menu(){
    puts("1. Add");
    puts("2. Delete");
    puts("3. View");
    puts("4. Edit");
    puts("5. Exit");
    printf("> ");
}
int read_int(){
    char buf[16];
    read(0,buf,16);
    return atoi(buf);
}
void add(){
    unsigned int size, idx;
    printf("Index : ");
    idx = read_int();
    if(idx > 9)
	exit(1);
    if(chuck[idx])
        exit(1);
    printf("size : ");
    size = read_int();
    chuck[idx] = malloc(size);
    use_chuck = chuck[idx];
}
void delete(){
    unsigned int idx;
    printf("Index : ");
    idx = read_int();
    if(idx > 9)
        exit(1);
    if(!chuck[idx])
        exit(1);
    free(chuck[idx]);
    chuck[idx] = NULL;
}
void view(){
    puts("~_~");
}
void edit(){
    unsigned int size;
    if(!use_chuck)
        return;
    printf("size : ");
    size = read_int();
    read(0,use_chuck,size);
    use_chuck = NULL;
}
int main(){
    int num;
    init();
    while(1){
        menu();
        num = read_int();
        switch(num){
            case 1:
		add();
		break;
	    case 2:
		delete();
		break;
	    case 3:
		view();
		break;
	    case 4:
		edit();
		break;
	    case 5:
		puts("bye");
		return 1;
	    default:
		puts("invalid menu");
        }
    }
}
