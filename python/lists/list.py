#!/bin/python3

def listy():
    l = list()
    l.append("apple")
    l.append("banana")
    l.append("cherry")
    print(l,len(l))
    n = list()
    for i in l:
        if i.find('a'):
            n.append(i)
    print(n)
    return n

def copy(a:list):
    b = a
    if a is b:
        print("same")

def main():
    copy(listy())
if __name__ == "__main__":
    main()
