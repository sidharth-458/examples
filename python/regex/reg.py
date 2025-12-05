#!/bin/python3

import re
def reg():
    s:str = "My name is Sidharth Seela"
    f_pat = "My name is ([^ ]+)"
    l_pat = "My name is [^ ]+ ([^ ]+)"
    print(re.findall(f_pat,s))
    print(re.findall(l_pat,s))
if __name__ == "__main__":
    reg()
