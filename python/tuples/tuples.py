#!/bin/python3

def tup():
    tup = ("F40",["V12",550,3.5],"Red")
    print(tup[0], tup[1])
    model = tup[0]
    engine = tup[1]
    color = tup[2]
    print(model,engine,color)

def cleanup(t:tuple)->tuple:
    new = tuple((int(t[0]), int(t[1])))
    return new

def t2l(t:tuple)->tuple[list,list]:
    y = list()
    x = list()
    for i in t:
        x.append(i[0])
        y.append(i[1])
    return x,y

def main():
    tup()
    print(cleanup(("11","22")))
    t = ((0,1),(1,2),(2,4),(3,8),(4,16))
    x,y = t2l(t)
    print(x)
    print(y)

if __name__  == "__main__":
    main()
