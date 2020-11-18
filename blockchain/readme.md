
### KUContract

```
Contract Address : 0xE184Ed7f82f9acBAffBd600C3dB7EE4F481665BA

Network : Kovan Testnet

```

#### Problem 1
```

문제 : hideenFlag 변수 읽기

난이도 : 어려움

해설 : Solidity bytecode decompile 또는 Deploy transaction decoding을 통해 flag를 복구할 수 있는가?

플래그 : KCTF{can.you.decompile.contract?}

```

#### Problem 2
```

문제 : xor된 flag 변수 읽기

난이도 : 쉬움

해설 : Solidity call을 사용할 수 있고 xor을 복호화할 수 있는가?

플래그 : KCFT{what.is.your.address?}

```

#### Problem 3
```

문제 : Unsafe variable

난이도 : 중간

해설 : block의 now를 계산하거나, call을통해 복호화할 수 있는가?

플래그 : KCTF{call.is.free}

```


KCTF{too.simple.underflow}

#### Problem 4
```

문제 : Interger undrflow

난이도 : 중간

해설 : playGame을 통해 잔액을 -로 만든 후 richGetFlag 호출

플래그 : KCTF{too.simple.underflow}

```