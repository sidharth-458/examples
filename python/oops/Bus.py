#/bin/python3
from Vehicle import Vehicle

class Bus(Vehicle):
    def __init__(self,wheels,surface,capacity):
        super().__init__(wheels,surface)
        self.capacity = capacity
    
    def __str__(self):
        s = super().__str__()
        return f"{s} and has got {self.capacity} capacity" 

    def move(self, direction):
        match direction:
            case "straight":
                print("centering wheel")
            case "right":
                print("turning right")
            case "left":
                print("turning left")
            case _:
                print("wrong dir")

class Fleet():
    total:int = 0

    def add(self):
        self.total += 1
        return Bus(6,"road",80)

if __name__ == "__main__":
    fleet = Fleet()
    volvo = fleet.add()
    print(fleet.total)
    volvo.move("straight")
    print(volvo)
