#!/bin/python3

def main():
    d = dict()
    d["Krishna"] = 12
    d["Rama"] = 11
    print(d)
    del d["Rama"]
    print(d)
    for i in d:
        print(i, d[i])

main()
