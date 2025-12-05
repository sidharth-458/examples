#!/bin/python3

class note:
    def __init__(self,title,sub):
        self.title  = title
        self.sub    = sub

    def __str__(self):
        return f"Title: {self.title}, sub: {self.sub}"

class next:
    pass

def main():
    a = note("a","b")
    print(a)
    print(type(a))
    b = next()
    print(type(b))


if __name__ == "__main__":
    main()
