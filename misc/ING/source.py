f=open('binary_flag.txt','r').read()
out = open('share','w')
a="ing?"
f=a.join(f)
f=f.replace('0','\t')
f=f.replace('1',' ')


out.write(f)

