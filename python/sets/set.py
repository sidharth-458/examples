#!/bin/python3

from itertools import combinations

def panagram():
    sentence = "    The quick brown fox jumps over a lazy dog"
    sentence = sentence.strip().replace(' ','')
    if not sentence.isalpha():
        print("has number")
        return
    a = set(sentence.strip().replace(' ',''))
    print(a)
    if len(a) == 26:
        print("Yes")

def main():
    a = { 1, 2 , 3 ,4 ,5}
    b = { 2, 3 ,6,8,1}
    print(a.union(b)) # union,intersection,isdisjoint,issubset, issuperset,difference,
    panagram()
    print(list(combinations(b,2)))

if __name__ == "__main__":
    main()
