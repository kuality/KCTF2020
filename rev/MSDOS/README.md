문자열을 입력받은 문자열이 sub_102C2함수를 통해서 바뀌게 된다.

그 결과값이 "amazing_mypass" 문자열과 같아야 한다.



sub_102C2에서 어셈을 보면 for문 형태를 띄고 있으며 분기문을 살펴보면 다음과 같다.

```assembly
seg000:02D8                 or      dx, dx
seg000:02DA                 jz      short loc_102FC
seg000:02DC                 cmp     dx, 1
seg000:02DF                 jz      short loc_102E8
seg000:02E1                 cmp     dx, 2
seg000:02E4                 jz      short loc_102F4
seg000:02E6                 jmp     short loc_10303
```

or dx, dx 연산을 했을때 jz(0일 경우) 점프를 한다. 같은 숫자를 or했을 때 0이 나오려면 0밖에 없다. 즉 0일 경우 점프를 하는 것이다. 즉 dx의 값이 0, 1, 2일 때 분기된다. 

dx의 값은 다음과 같이 설정된다.

```assembly
seg000:02D0                 mov     ax, si
seg000:02D2                 mov     bx, 3
seg000:02D5                 cwd
seg000:02D6                 idiv    bx
```

si의 값을 ax에 넣고 bx에 3을 넣고 idiv bx를 진행하는데 이는 ax / bx 를 의미하는 것이다. 그리고 나머지는 dx레지스터의 저장된다. 즉 si % 3 의 값이 dx로 설정되는 것이다.

어셈을 더 살펴보면 si에 값은 0부터 시작하여 입력했던 문자열의 길이만큼 반복문을 돌게되는것을 확인 할 수 있다.

그러면서 분기문을 통해서 입력했던 문자열의 값을 조금씩 수정하는 것을 확인할 수 있다. 

```assembly
seg000:02E8 loc_102E8:                              ; CODE XREF: sub_102C2+1D↑j
seg000:02E8                 mov     bx, si
seg000:02EA                 mov     al, [bx+di]
seg000:02EC                 add     al, 0FDh ; 'ý'

seg000:02F4 loc_102F4:                              ; CODE XREF: sub_102C2+22↑j
seg000:02F4                 mov     bx, si
seg000:02F6                 mov     al, [bx+di]
seg000:02F8                 add     al, 2
seg000:02FA                 jmp     short loc_102EE

seg000:02FC loc_102FC:                              ; CODE XREF: sub_102C2+18↑j
seg000:02FC                 mov     bx, si
seg000:02FE                 xor     byte ptr [bx+di], 1
seg000:0301                 jmp     short $+2
```

0 일 경우 입력받은 문자열[n] ^ 1

1 일 경우 입력받은 문자열[n] + 0xFD(실제로는 -3이 더해짐 2의 보수)

2 일 경우 입력받은 문자열[n] + 2

따라서 이에 대한 역연산 코드를 작성해보면 다음과 같다.



```python
key = "amazing_mypass"
flag = ""
for i in range(len(key)):
    j = i%3
    if(j==0):
        flag += chr(ord(key[i]) ^ 1)
    elif(j==1):
        flag += chr(ord(key[i]) + 3)
    elif(j==2):
        flag += chr(ord(key[i]) - 2)
print flag #`p_{llfbkxs_rv
```

``KCTF{`p_{llfbkxs_rv}``

