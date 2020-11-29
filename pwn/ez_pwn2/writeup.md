# ez_pwn2

#### by. dubini0



\*\* 원래 의도한 대로 수정하였습니다. CTF때와 문제가 다릅니다. \*\*



취약점 : talk함수에서 amount의 주소가 아닌 amount의 값에 입력을 받습니다. 따라서 BOF를 이용해 amount함수에 puts의 got를 입력한 뒤, amount의 값(puts의 got)에 win함수의 주소를 입력하면 마지막 got overwrite가 된 puts함수가 실행되면서 문제가 풀립니다.



```c
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
```



+) CTF당시에는 scanf함수여서 바로 ret에 win함수를 넣어도 풀렸습니다. 이는 문제의 의도와 어긋나기 때문에 수정하였습니다.
