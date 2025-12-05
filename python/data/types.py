#!/usr/bin/python3

def main():
    inp:str = input("Enter number");
    print(inp)
    print(type(float(inp)))
    print(type(int(inp)))
    _data = 1
    print("Python's \"Syntax\" is easy")
#    print("helo" + 5)
    none = None
    print(type(none))
    mystr:str = "PythonProgramming"
    rev:int = mystr[::-1].find('P')
    forw:int = len(mystr) - rev
    print(mystr[0:forw - 1])
    print(mystr[forw - 1:])
    a = b = 10
    b = 20
    print(a)
    print(b)
    a = (5)
    b = (5,)
    print(type(a))
    print(type(b))
#    l = []
 #   l.append("a")
  #  l.append("b")
   # dicti = {}
    #dicti[l] = "ab"
    stri ="5"
    num = 5
    num = num * stri
    print(type(num))
    char = 'c'
    print(type(char))
    char = "c"
    print(type(char))
    print(type('''c'''))
    if str == type(char):
        print("yes")
    if isinstance(char,str):
        print("yes")
#    $v = 1
#    @b = 2
if __name__ == "__main__":
    main()
