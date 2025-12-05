#!/bin/python3

import re
def basic():
    f = open("c.c")
    content = f.read()
    content = content.replace("\n"," ");
    
    content = content.replace("\t"," ");
    print(content)
    s = set(content.split())
    print(s)
    f.close()
def parseError():
    l = list()
    with open("out.txt") as f:
        for line in f:
            r= re.match("(ERROR:[^\n]+)",line)
            if r:
                l.append(r.group())

    print(l)
if __name__ == "__main__":
    basic()
    parseError()
