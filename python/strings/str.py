#!/usr/bin/python3
def main():
    name:str = "    Sidharth Seela  " 
    print(name[0:10])
    print(name[::-1])
    print(name[-5:-1])
    print(name.strip())
    print(name.upper())
    print(name.lower())
    print(name.replace(name.strip().split()[0],"Sai"))
    l = ["apple","banana","cashew"]
    new = " ".join(l)
    print(f"my name is {new}")
    del name
    print(name)
if __name__ == "__main__":
    main()
