key = 863245052
flag = "KCTF{simple_m0dulus_calculation}"
cipher = int(flag.encode("hex"),16)^key
print(cipher)