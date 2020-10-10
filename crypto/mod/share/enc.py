key = ?
flag = "?"
cipher = int(flag.encode("hex"),16)^key
print(cipher)