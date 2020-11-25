CRYPTO

1. **Mod**

   ```python
   p=2147483647
      q=101
      q^a % p = 673919365
      q^b % p = 992233731
      key = ?"""
   
   
   key = ?
   flag = "?"
   cipher = int(flag.encode("hex"),16)^key
   print(cipher)
   #output : 34042424043975417532695192363865173478379846807857716823902432060409124715649
   ```

   Diffie-hellman key exchange 과정에서의 key는 q^(axb) mod p 입니다.

   

   exploit code 

   ```python
     
   g = 101
   p = 2147483647
   for i in range(0,100):
       print(str(i)+" "+str((g**i)%p)) #a, b 찾기
   a=
   b=
   key=(q**(a*b))%p
   #a=43, b=74, key = 863245052
   ```

   KCTF{simple_m0dulus_calculation}

   (xor 과정에서  byte별로 하지않아 flag가 노출되었습니다 ㅠ)

   

2. **What is ur code?**

   ```c
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
   ```

   한글자마다 매칭을 해서 passcode를 확인하는 과정에서 생기는 취약점입니다. 

   exploit code 

   ``` python
   from pwn import *
   import time
   f_pw = ''
   r = remote("163.152.225.231",12350)
   r.recvuntil("INPUT PASSCODE")
   for x in range(10)
   	for y in range(0x6a, 0x7a):
       	betime = time.time()
       	r.sendline(chr(y)+"\n")
     	    r.recvuntil("try again")
       	aftime = time.time()
       	if(aftime - betime < 1.7):
           	f_pw += chr(y)
   r.sendline(f_pw)
   
   
   ```

   KCTF{you'll_kn0w_that_life_is_Timing}

   

3. Korean

   ```
   풰굪뫠퀴릐폦녶햐쉗뭬뮤퀿힂
   툐햜뮂미픶믶눼풰퀃뭐훂믧풔
   싚팢뭐퉤햐퓆픠굪뭝묲례믥믜 
   ?
   KCTF{?}
   
   hint : 
   
   ㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅋㅌㅍㅎ
   ㅏ  ㅐ  ㅑ ㅒ ㅓ ㅔ  ㅕ ㅖ ㅗ ㅘ ㅙ ㅚ ㅛ ㅜ ㅝ ㅞ ㅟ ㅠ ㅡ ㅢ ㅣ
   ㄱ ㄲ ㄳ ㄴ ㄵ ㄶ ㄷ ㄹ ㄺ ㄻ ㄼ ㄽ ㄾ ㄿ ㅀ ㅁ ㅂ ㅄ ㅅ ㅆ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ
   ```

   한글의 초, 중, 종성을 주어진 치환표에서 카이사르 암호처럼 3, 6, 9칸씩 밀어서 암호화 하였습니다 :D

    

   exploit

   ```
   ㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅋㅌㅍㅎ(14)
   ㅌㅍㅎㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅋ(초성) 3
   
   ㅏ  ㅐ  ㅑ ㅒ ㅓ ㅔ  ㅕ ㅖ ㅗ ㅘ ㅙ ㅚ ㅛ ㅜ ㅝ ㅞ ㅟ ㅠ ㅡ ㅢ ㅣ (21) 6
   ㅞ  ㅟ  ㅠ ㅡ ㅢ ㅣ  ㅏ ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅗ ㅘ ㅙ ㅚ ㅛ ㅜ ㅝ (중성)
   
   ㄱ ㄲ ㄳ ㄴ ㄵ ㄶ ㄷ ㄹ ㄺ ㄻ ㄼ ㄽ ㄾ ㄿ ㅀ ㅁ ㅂ ㅄ ㅅ ㅆ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ (27) 9
   ㅅ ㅆ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ ㄱ ㄲ ㄳ ㄴ ㄵ ㄶ ㄷ ㄹ ㄺ ㄻ ㄼ ㄽ ㄾ ㄿ ㅀ ㅁ ㅂ ㅄ (종성)
   ```

   KCTF{사랑했기때문에}

   

4. RSA

   ```
   binary file, pem file
   ```

   먼저 pem인증서파일에서 openssl을 통하여 n과 e를 구합니다.
   >> openssl rsa -pubin -inform PEM -text -noout -in publickey.pem

   그리고 구한 n, e를 첨부한 RSAwienerHacker.py 코드에 넣으면 d를 구할 수 있고 d를 구했으면 복호화가 가능합니다.
   (출처 : https://github.com/pablocelayes/rsa-wiener-attack)

   ```python
   import ContinuedFractions, Arithmetic, RSAvulnerableKeyGenerator
   from gmpy2 import *
   from Crypto.Util.number import *
   from Crypto.PublicKey import RSA
   
   def hack_RSA(e,n):
       frac = ContinuedFractions.rational_to_contfrac(e, n)
       convergents = ContinuedFractions.convergents_from_contfrac(frac)
       
       for (k,d) in convergents:
           
           #check if d is actually the key
           if k!=0 and (e*d-1)%k == 0:
               phi = (e*d-1)//k
               s = n - phi + 1
               # check if the equation x^2 - s*x + n = 0
               # has integer roots
               discr = s*s - 4*n
               if(discr>=0):
                   t = Arithmetic.is_perfect_square(discr)
                   if t!=-1 and (s+t)%2==0:
                       print("Hacked!")
                       return d
   ##################################################출처 : https://github.com/pablocelayes/rsa-wiener-attack
   
   e = 187224198358976786579749067995497890905799822947128651088251530361387419780131539700347226362649795586438751501544451473659148049507814353125472665954342709257182749776947194758327083239358991106508477303866175029695125086636425667367941964361682844471490598884007406957886946810963902666192471332550759161305
   n = 237513265686025789186562608732400008100581870458434017952788114554225756652162413702306473956172406315118900180084859436965775540087331299252158189935099309726131944473377703166550089276072127708850460299073570538050902891628197488607150799868080449908160852741234270848472245085906293581136277333188361835161
   
   
   d = hack_RSA(e,n)
   
   cyp = "0x2393118ecdee71b12de76cb3bc14dd5dd10e5807e06593d3e2e96b1e53d48592d15da092377299bc66290c661ad0c29c8d12354da0c188c799ae21a29f8062487e0543a2a714d68a37f0f98e102ea0bd5df186c2c2f8fbf277329b8e017e6898d19ad707ccd3b75c1af4bda00ac9cb9710cb7e37bedd7b71d92c000c00b867e8"
   cyp = int(cyp,16)
   
   dec = (hex(pow(cyp,d,n)))
   #covert hex to ascii >> solved
   ```

   ```python
   '''
   Created on Dec 22, 2011
   
   @author: pablocelayes
   '''
   
   def egcd(a,b):
       '''
       Extended Euclidean Algorithm
       returns x, y, gcd(a,b) such that ax + by = gcd(a,b)
       '''
       u, u1 = 1, 0
       v, v1 = 0, 1
       while b:
           q = a // b
           u, u1 = u1, u - q * u1
           v, v1 = v1, v - q * v1
           a, b = b, a - q * b
       return u, v, a
   
   def gcd(a,b):
       '''
       2.8 times faster than egcd(a,b)[2]
       '''
       a,b=(b,a) if a<b else (a,b)
       while b:
           a,b=b,a%b
       return a
   
   def modInverse(e,n):
       '''
       d such that de = 1 (mod n)
       e must be coprime to n
       this is assumed to be true
       '''
       return egcd(e,n)[0]%n
   
   def totient(p,q):
       '''
       Calculates the totient of pq
       '''
       return (p-1)*(q-1)
   
   def bitlength(x):
       '''
       Calculates the bitlength of x
       '''
       assert x >= 0
       n = 0
       while x > 0:
           n = n+1
           x = x>>1
       return n
   
   
   def isqrt(n):
       '''
       Calculates the integer square root
       for arbitrary large nonnegative integers
       '''
       if n < 0:
           raise ValueError('square root not defined for negative numbers')
       
       if n == 0:
           return 0
       a, b = divmod(bitlength(n), 2)
       x = 2**(a+b)
       while True:
           y = (x + n//x)//2
           if y >= x:
               return x
           x = y
   
   
   def is_perfect_square(n):
       '''
       If n is a perfect square it returns sqrt(n),
       
       otherwise returns -1
       '''
       h = n & 0xF; #last hexadecimal "digit"
       
       if h > 9:
           return -1 # return immediately in 6 cases out of 16.
   
       # Take advantage of Boolean short-circuit evaluation
       if ( h != 2 and h != 3 and h != 5 and h != 6 and h != 7 and h != 8 ):
           # take square root if you must
           t = isqrt(n)
           if t*t == n:
               return t
           else:
               return -1
       
       return -1
   
   #TEST functions
   
   def test_is_perfect_square():
       print("Testing is_perfect_square")
       testsuit = [4, 0, 15, 25, 18, 901, 1000, 1024]
       
       for n in testsuit:
           print("Is ", n, " a perfect square?")
           if is_perfect_square(n)!= -1:
               print("Yes!")
           else:
               print("Nope")
   
   if __name__ == "__main__":
       test_is_perfect_square()
   ```

   ```python
   '''
   Created on Dec 14, 2011
   
   @author: pablocelayes
       
   '''
   
   def rational_to_contfrac(x,y):
       '''
       Converts a rational x/y fraction into
       a list of partial quotients [a0, ..., an]
       '''
       a = x//y
       pquotients = [a]
       while a * y != x:
           x,y = y,x-a*y
           a = x//y
           pquotients.append(a)
       return pquotients
   
   #TODO: efficient method that calculates convergents on-the-go, without doing partial quotients first
   def convergents_from_contfrac(frac):
       '''
       computes the list of convergents
       using the list of partial quotients
       '''
       convs = [];
       for i in range(len(frac)):
           convs.append(contfrac_to_rational(frac[0:i]))
       return convs
   
   def contfrac_to_rational (frac):
       '''Converts a finite continued fraction [a0, ..., an]
        to an x/y rational.
        '''
       if len(frac) == 0:
           return (0,1)
       num = frac[-1]
       denom = 1
       for _ in range(-2,-len(frac)-1,-1):
           num, denom = frac[_]*num+denom, num
       return (num,denom)
   
   def test1():
       '''
       Verify that the basic continued-fraction manipulation stuff works.
       '''
       testnums = [(1, 1), (1, 2), (5, 15), (27, 73), (73, 27)]
       for r in testnums:
           (num, denom) = r
           print('rational number:')
           print(r)
   
           contfrac = rational_to_contfrac (num, denom)
           print('continued fraction:')
           print(contfrac)
   
           print('convergents:')
           print(convergents_from_contfrac(contfrac))
           print('***********************************')
   
   if __name__ == "__main__":
       test1()
   
   ```

   

   KCTF{We1l_kn0wn_rSa_ATTAcK}

**MISC**

```
	ing? ing?	ing?	ing? ing?	ing? ing? ing?	ing? ing?	ing?	ing?	ing?	ing? ing? ing?	ing? ing?	ing? ing?	ing? ing?	ing?	ing?	ing? ing?	ing?	ing?	ing? ing? ing?	ing?	ing? ing? ing? ing? ing?	ing? ing? ing?	ing? ing?	ing? ing?	ing? ing? ing? ing?	ing? ing? ing?	ing?	ing?	ing?	ing? ing?	ing? ing? ing? ing?	ing?	ing? ing?	ing?	ing? ing? ing?	ing? ing? ing?	ing? ing?	ing? ing? ing?	ing? ing?	ing?	ing? ing?	ing? ing? ing?	ing? ing? ing? ing?	ing?	ing? ing? ing?	ing?	ing? ing? ing? ing?	ing? ing?	ing? ing? ing? ing? ing? ing?	ing? ing? ing? ing?	ing? ing?	ing? ing?	ing? ing? ing? ing?	ing?	ing?	ing?	ing?	ing? ing?	ing? ing? ing? ing? ing? ing?	ing? ing? ing? ing?	ing? ing?	ing? ing?	ing? ing? ing? ing?	ing?	ing? ing?	ing?	ing? ing?	ing? ing? ing? ing? ing? ing?	ing? ing? ing?	ing?	ing?	ing? ing?	ing?	ing? ing? ing? ing?	ing?	ing? ing?	ing?	ing? ing? ing?	ing?	ing?	ing?	ing? ing?	ing? ing? ing?	ing? ing?	ing?	ing? ing?	ing? ing? ing?	ing? ing? ing? ing?	ing?	ing? ing? ing? ing? ing? ing?	ing? 
```

source code 

```python
f=open('binary_flag.txt','r').read()
out = open('share','w')
a="ing?"
f=a.join(f)
f=f.replace('0','\t')
f=f.replace('1',' ')


out.write(f)

```

exploit code 

```python
f=open('share','r').read()

for i in range(256):
    if i == ord(' ') or i == ord('\t'):
        continue
    f=f.replace(chr(i),'')

f=f.replace('\t','0')
f=f.replace(' ','1')
n=""
def convert(s):
    return ''.join(chr(int(s[i*8:i*8+8],2)) for i in range(len(s)//8))
print(convert(f))

```

( 참고 자료: https://joizel.readthedocs.io/ko/latest/misc/[2015_defcamp]%20[MISC]%20try_harder.html)

KCTF{Warming_up_ur_brain}