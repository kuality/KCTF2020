# 한입만



간단한 rop문제.

read로 256바이트나 입력받기때문에 이를 이용하여 rop를 이용한다.

##### 과정

1. write()함수로 read()함수 주소 leak (b/c aslr)
2. bss영역에 `/bin/sh`저장 
3. write()함수의 got에 system()함수의 주소로 GOT overwrite
4. write() + binsh 인자로 호출하여 exploit