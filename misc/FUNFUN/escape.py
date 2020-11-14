#! /usr/bin/python3
import random

def main():
    op_box = ["+","-","*","//"] 
    print("Welcome To Four rules calculation Game in Python")
    count = 0

    while(True):
        if(count == 100):
            print("What is Your Name : ")
            name = input()
            for keyword in ['eval', 'exec', 'import', 'open', 'os', 'read', 'system', 'write']:
                if keyword in name:
                    print("No!!!!")
                    exit(0)
                else:
                    exec(name)

        x = random.randint(1, 1000000)
        y = random.randint(1, 1000000)
        z = random.randint(0,3)
        Random_Question = str(x)+str(op_box[z])+str(y)
        print(Random_Question, '=', end='')
        answer = int(input())
        if answer == eval(Random_Question):
            print("Right!!!")
            count += 1
        else:
            print("Try again!!")
        
if __name__ == "__main__":
    main()