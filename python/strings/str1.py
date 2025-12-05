#!/bin/python3


def palin(s:str)->bool:
    l:int = len(s)
    for i in range(int(l/2)):
        if(s[i] != s[l - i - 1]):
            return False
    return True

def length(s:str)->int:
    i:int = 0
    for char in s:
        i+=1
    return i

def maxx(s:str)->int:
    ht = dict()
    m = -1
    c:str = ""
    for char in s:
        char = str(char)
        if char in ht.keys():
            ht[char] += 1
        else:
            ht[char] = 1

    for i in ht:
        if ht[i] > m:
            m = ht[i]
            c = i

    return ord(c)



def main():
    print(palin("hello"),palin("madam"))
    print(length("hello"))
    print(chr(maxx("hello")))

if __name__ == "__main__":
    main()
