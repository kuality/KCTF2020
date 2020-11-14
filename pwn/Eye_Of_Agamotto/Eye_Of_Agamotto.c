#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
//gcc -o Eye_Of_Agamotto Eye_Of_Agamotto.c -fstack-protector -m64 -no-pie -mpreferred-stack-boundary=2 -z now
char *p, **p1;
int seed = 0x12983476;

void menu(){
    puts("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhyyyyyyyyyyyyysoos/ososyyyyyyyyyyyyyyyyyysssssssssssssssssssssssoo");
    puts("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhyyyyyyso/:..```..---:-:/++osyyyyyyyyyyyyssssssssssssssssssssssss");
    puts("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhyyyy+:``  `....----.......-:+syyyyyyyyyyyyyyyyyyyyssssssssssssss");
    puts("dddddddhhhhhhdhhhhhhhhhhhhhhhhhhhhhhyy/``  `..--.----.``````  `.-.-/syyyyyyyyyyyyyyyyyssssssssssssss");
    puts("dddddddddddddddddddddddhhhhhhhhhhhhhy/`  ``.``----.`````  ``   .:.`.:syyyyyyyyyyyyyyyyyyysssssssssss");
    puts("ddddddddddddddddddddddddddddhhhhhhhyo`   `.```.:+/.`--``  ``-`.--..``-yyyyyyyyyyyyyyyyyyyyyyyyssssss");
    puts("dddddddddddddddddddddddddddddhhhhhhy-` ``.````-/:``.:-.```.-:--..--``.oyyyyyyyyyyyyyyyyyyyyyyyssssss");
    puts("ddddddddddddddddddddddddddddddhhhhh+``````..``-.`....-::/+ohddho:..` `:yyyyyyyyyyyyyyyyyyyyyyyyyssss");
    puts("ddddddddddddddddddddddddddddddhhhhh+```  `/./.-:/ss.o/+mmmmmmmmmh:``  .+yyyyyyyyyyyyyyyyyyyyyyyyssss");
    puts("ddddddddddddddddddddddddddddddddhhh:``  `.:/o-./shd:hs:mNNNNmmmmd+`   `/yyyyyyyyyyyyyyyyyyyyyyyyyyss");
    puts("dddddddddddddddddddddddddddddddddhh-    `.-+++-/oshyshoyNNNNNmmmdo.   `+yyyyyyyyyyyyyyyyyyyyyyyyyyys");
    puts("ddddddddddddddddddddddddddddddddddh/`    ..:so+/oyyhdmmdmNNNNmmmds/-...oyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
    puts("ddddddddddddddddddddddddddddddddddd/.```....:+osyhhdmmmmmmNNNmmmmdh/-.`shhhhhhhhhhhyyyyyyyyyyyyyyyyy");
    puts("dddddddddddddddddddddddddddddddddddh-```.-.-/osyhdmmNmmmNmmNNmdhyyd+-`.shhhhhhhhhhhhhyyyyyyyyyyyyyyy");
    puts("ddddddddddddddddddddddddddddddddddddy:```-.`-:+oshddmmdddyss+///+ydy-`+hhhhhhhhhhhhhhhhyyyyyyyyyyyyy");
    puts("mmdddddddddddddddddddddddddddddddddddy.``-...```.--:+sdmh+//++syhmmdsoyhhhhhhhhhhhhhhhhhyyyyyyyyyyyy");
    puts("mmmddddddddddddddddddddddddddddddddds-/:..-/:-:+os+-.+mNmmmddmmmNNmhhhhhhhhhhhhhhhhhhhhhhyyyyyyyyyyy");
    puts("mmmmmmdddddddddddddddddddddddddddddo` `//../+oshddy:.:hNmmNmmNNNNmdso.:ohhhhhhhhhhhhhhhhhhyyyyyyyyyy");
    puts("mmmmmmmmmddddddddddddddddddddddddds.   `--.-+sydmds-..smmmmmNNNmmdy/` ``:shhhhhhhhhhhhhhhhhyyyyyyyyy");
    puts("mmmmmmmmmmmmdddddddddddddddddddddh-`      `.-/ohddo-..smmmmddmmmdhs``````.+yhhhhhhhhhhhhhhhhyyyyyyyy");
    puts("mmmmmmmmmmmmmmddddddddddddddddddd+`        ..-:/so::.`-shyymddmmdh+````````-shhhhhhhhhhhhhhhyyyyyyyy");
    puts("mmmmmmmmmmmmmdddddddddddddddddddy--.`      ..--:/+//-`.:osysyydmdy.``.``````./yhhhhhhhhhhhhhhhhhyyyy");
    puts("mmmmmmmmmmmmmmmmdddddddddddddddh:.---``    `-.-:/:-.``-///so+osoh/```-o/``````-+yhhhhhhhhhhhhhhhhyyy");
    puts("mmmmmmmmmmmmmmmmddddddddddddddds-.--::-``  `:/..-./--:+oyhddmmdoo.```-yd:`````.-ohhhhhhhhhhhhhhhhyyy");
    puts("mmmmmmmmmmmmmmmmddddddddddddddddy+:--::-.`  -o+-.-o:--/++oyhddd/-````.+dh```.:oyhhhhhhhhhhhhhhhhhyyy");
    puts("mmmmmmmmmmmmmmmmmmddddddddddddddddho:::::-.``+so-`-/+/:/+ydmmds-``````-ym-.:ohhhhhhhhhhhhhhhhhhhhhyy");
    puts("mmmmmmmmmmmmmmmmmmddddddddddddddddhs--:////-`-+so-`.+ooosyyyy+/` `````-ymhohhhhhhhhhhhhhhhhhhhhhhhyy");
    puts("mmmmmmmmmmmmmmmmddddddddddddddho/-.   `-///:.`-/oo/-`....-::--.  `````-omNh+sysoossyyyyhhhhhhhhhhyyy");
    puts("mmmmmmmmmmmmmmmdddddddddddhyy/.`     `  `-/:-   .+o+/:/++-.```   ````..:yNm+.-..`.---::::+syyhhhhyyy");
    puts("mmmmmmmmmmmmmmmdddddddhs+-..``        `   .::`  `.+syyho:..``    ``.::/+yddd/..`````...````.-+shhhhy");
    puts("mmmmmmmmmmmmmddddhs+::-```````             `/. `./yddh+/..-.`  `-/oyhdmmmms+ds:-.````........../yhhh");
    puts("mmmmmmmmmmmmddy+:-..........````            .:.:+dddd++-....``-sddmhssoo+sh/odhhhs:```........``:shh");
    puts("dmmmmmmmmmmmh:```..`......------.```        `:oyysy+///..--``.`/sy+-...-/osh++ddddd/.```........-:hh");
    puts("mmmmmmmmmddh/`...-/-.-.....`...----...`` `./+shyo+-`...-::..-` .:y/.--::////o-+yhddd+`````...-...-+h");
    puts("mmmmmmmddhs-.`...-::----.....-.......-...:shhhsyo.```..---.:-``::++oyhys:....-`:yddho```````.-:::::+");
    puts("mmmdddmdo-.`.`.`...---..----::../:...``-+oydhyy/`..---.:-`-:/.`/symdho/.`-:.:../sdmho`````````.-::::");
    puts("ddddddy--``` ````.```..`......`.:/:-..:hdshsss/....---.-.`::/.:hdhss+/o+:-:.:-./sdmdo.``````````.---");
    puts("ddddds.-.`````.``/:-`` ``````````-:-/shyo+yhy::...--.-.. .://./ys-:shhmmdo/.:-.+ymNms...`````````..-");
    puts("ddddy...``  ```.`://:.``..````````:oyssossddh+:.-.----.``:://::ss//:+ydNNmy-/::shdmms...-..`````````");
    puts("dddd-`` `````````.:--. `--....``.-shds+smmhydh+-..----` .:://--+h/+-:+ydmmh-/:shshh+...o+----..`````");
    puts("ddd/``````````````---` `...`.``..:osoosyhdmdssh+-.-///:`-://+:.+yo-..-/syho-/:ods/.....sho--....-..`");
    puts("ddo`  ``````````` ..`  ````..```-/+hmdy..:+shoyhs-/o++/.-:/++/`++:.``...-::-:---````..-syo:--.------");
    puts("dd.```  ````````` ```   ``.`.` -/o+hdh:`/osooh/yds.--.`--:/+++.....-...`.`..``  `````.+oo+....-//---");
    puts("d+````````````          ````   `+shhds`/oosyos/::-...`.-:/++++:-.```--/:-`         `-/++/..-:o:.oo:-");
    puts("/`````````````        `..-:.   ``/yhds-syysoso-``.--.`--//++++-.-.-`-``.....`   `.-:/:-..-:+so/`-s+/");
    puts("`````````````     ```.--//+:`  ```./ss+yyys+-` `.-:-``--://++:..--:.-::..````````.-.```.:+o+os/`.ooo");
    puts("`````````````.-```.`.-/-:+//-.  `````./+/:.` `.`.--.`.`.--:::.`:.-:.-::--.:.`    ```.-.-:::///.`:++o");
    puts("```````````:+/o:../.-:/-.:/::-.  `` ```       `.`-..```..-:-.`. .-.`.---..:::.`       ``..-.`.``++++");
    puts("::---.`...`-++/oo:+---//..-/:/:.   `       `   `.```````..-.``` `.``....`..----`      ````.````:+/+:");
    puts("-:::``.:-.---/+:o+o-..-::...-::.  `.` ```       `.``.----...```  ``````````.`...`         ` ``-:://.");
    puts("::/:`..::-/:-.-:/+os.`...----.` `  -.`.`` `     `-///+o/+/:-`        `   ````````         `````.-.``");
    puts("/:+/`.:::-:/:....+/oo-``--..`   .  `-.``.  ```.-/++s//o:::/:-.`                         ``     ```..");
    puts("+:/o..:+:-::/...`-+://. ``      .`  --.`.````.+ho/:+++:.-:----.                         ` `    ```.-");
    puts("//-/:`.++:-::..```//-:.      `  ..  .--`-.. ``+y+/oso+o-:+:--:-                          `    ``````");
    puts(":::+.`.:/:-.-.````-`           `-` `-...--` `.:++o+so///:/-:-.                          ` `         ");
    puts(":-:/:/:-..---..```               .-` `..`:-.`  `.://o++++:::-``                            ` ``     ");
    puts("`.--::::/::-.-..`                `..``..`.-..`   ``.--:::-`  ``                        ``  ````     ");
    puts("..``.-------.`       ` `             `````....`..``....``` `````                      `````  ```    ");
    puts(".`..`````  `         ```          `    ````-::-:-.----.``````````                     `````   `     ");
    puts(" ``....` .-.`    `   `.`          ``````....``...``--............```                     ` `  ``    ");
    puts("Dormammu!!! I've come to bargain.");
    puts("[1] Enter your lines");
    puts("[2] Restart");
    puts("[3] Help");
    puts("[Different Value] exit");
    
}

void check(){  //canary leak + input() func read(**)
    char name[100];
    int idx;
    p = name;
    puts("Input Name");
    scanf("%98s", p);
    printf("your name : %s\n", p);
    puts("Input Number");
    scanf("%10d", &idx);
    write(1, p+idx,1); 
    puts("");
}


int input(){
    int check;
    char memo[50];
    int fun = rand();
    puts("Input check");
    scanf("%d", &check);
    if(fun != check)
	p = memo;
    puts("Enter your lines");
    write(1, "> ", 1);
    read(0, (unsigned long long)p, 0x64);
    printf("%s", p);
    return 0;
}

void help(){
    char name[100];
    p = name;
    p1 = &p; 
    
    puts("Who you want?");
    scanf("%98s", &(*p1));
    //printf("%s came!!\nI will help you!!\n", p1);
}

int main(){
    setvbuf(stdout,0, 2, 0;
    setvbuf(stdin, 0, 1, 0);
    int num;
    srand(seed);    
    check();
    while (1){
        menu();
        write(1, "> ", 1);
        scanf("%1d", &num);
        switch (num){
        case 1:
            input();
            break;
        case 2:
            check();
	    break;
	case 3:
	    help();
	    break;
        default:
            exit(0);
        }
    }
    return 0;
}
