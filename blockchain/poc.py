import json
import time

from web3 import Web3, HTTPProvider
from web3.exceptions import TransactionNotFound

web3 = Web3(HTTPProvider("** Your Ropsten Key Here **"))
address = '0x3842c11aED733eaE9261C9190Fa46161959F1999'
abi = json.loads(open('abi.json').read())
contract = web3.eth.contract(address=address, abi=abi)

wallet_addr = '** Your Wallet Address Here **'
wallet_private_key = '** Your Wallet Private Key Here **'


def prob1():
    # flag = KCTF{can.you.decompile.contract?}
    pass


def prob2():
    # Solution 1
    res = contract.functions.getMyFlag().call({'from': wallet_addr})
    key = int(wallet_addr[-2:], 16)
    print(''.join(map(lambda x: chr(x ^ key), res)))

    # Solution 2
    res = contract.functions.getMyFlag().call({'from': '0x0000000000000000000000000000000000000000'})
    print(''.join(map(chr, res)))


def prob3():
    block_confirmation_timestamp = 1605688000

    i = block_confirmation_timestamp % 50000
    flag = contract.functions.guessIndex(i).call({'from': wallet_addr})
    print(flag)

def prob4():
    # Solution 1
    while True:
        money = contract.functions.showMoney().call({'from': wallet_addr})
        print(f"My money : {money}")
        if money < 0:
            break
        raw_tx = contract.functions.playGame(1).buildTransaction({
            'from': wallet_addr,
            'nonce': web3.eth.getTransactionCount(wallet_addr)
        })
        signed_tx = web3.eth.account.signTransaction(raw_tx, wallet_private_key)
        tx_hash = web3.eth.sendRawTransaction(signed_tx.rawTransaction)
        while True:
            try:
                web3.eth.getTransactionReceipt(tx_hash)
                break
            except TransactionNotFound:
                time.sleep(1)
                continue
    flag = contract.functions.richGetFlag().call({'from': wallet_addr})
    print(flag)

    # Solution 2
    flag = contract.functions.richGetFlag().call({'from': '0x7ebd33922276237c517D9C8c8B5D0048fd8E04B0'})
    print(flag)


if __name__ == '__main__':
    prob2()
    prob3()
    prob4()
