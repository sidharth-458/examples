
class Vehicle:
    def __init__(self,wheels,surface):
        self.wheels = wheels
        self.surface = surface

    def __str__(self):
        return f"has {self.wheels} wheels on {self.surface}"

