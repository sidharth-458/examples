#!/bin/python3

def temp(a:int):
    if a > 25:
        print("warm")
    elif a > 17 and a <=25:
        print("temperate")
    else:
        print("cold")

def state(a:int):
    match a:
        case 0:
            print("default")
        case 1:
            print("slow")
        case 2:
            print("med")
        case 3:
            print("fast")
        case _:
            print("error")

def main():
    temp(13)
    state(-1)


if __name__ == "__main__":
    main()
