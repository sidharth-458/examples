#!/bin/python3

def print_deet(name:str,age:int):
    if not len(name):
        print("invalid name")
        return
    if age < 0:
        print("invalid age")
        return 
    print(f"Name:{name},age:{age}")

def isNeg(a:int)->bool:
    return True if a>>31 else False

def fib(num:int)->int:
        match num:
            case 0 | 1:
                return 1
            case num if num < 0:
                print("error invalid input")
                return -1
            case _:
                return  fib(num -1) + fib(num -2)
        

def main():
    print_deet("alice",32)
    print(isNeg(12),isNeg(-12))
    print(fib(3))


if __name__ == "__main__":
    main()
