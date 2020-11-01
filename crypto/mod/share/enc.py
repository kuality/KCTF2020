"""p=2147483647
   q=101
   q^a % p = 673919365
   q^b % p = 992233731
   key = ?"""


key = ?
flag = "?"
cipher = int(flag.encode("hex"),16)^key
print(cipher)