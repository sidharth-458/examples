#!/bin/python3

import math

def sumcube():
    start:int = 100
    for i in range(100,999):
        string = str(i)
        summation = (int(string[0])) ** 3 + (int(string[1])) ** 3 + (int(string[2])) ** 3
        if summation == i:
            print(i)

def revnum():
    num:int = 123
    l = []
    digits = math.ceil(math.log(123,10))
    rev:int = 0
    for i in range(digits):
        rev += (num % 10) * (10 ** (digits - i -1))
        num = int(num / 10)
    print(rev)


def box(a:int):
    print("*"*a)
    print((a-2)*("*" + " "* (a - 2) + "*\n"),end="")
    print("*"*a)

def main():
    sumcube()
    revnum()
    box(12)

if __name__ == "__main__":
    main()
