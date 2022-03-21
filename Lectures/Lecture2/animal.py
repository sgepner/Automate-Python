class Animal:
    phylum = 'not defined'
    __isextinct = 'No' # ??

    def __init__(self, phy):
        self.phylum = phy

    def no_letters(self):
        return len(self.phylum)-1

    def SetExtinct(self, val):
        self.__isextinct = val
    def GetExtinct(self):
        return self.__isextinct

    def IsWarm(self):
        return self.isWarm

class Mamal(Animal):
    isWarm = 'Yes'
    def __init__(self):
        Animal.__init__(self, 'ssaki')

class Reptile(Animal):
    isWarm = 'No'
    def __init__(self):
        Animal.__init__(self, 'gady')

class Dog(Mamal):
    def __init__(self):
        Mamal.__init__(self)

class Cat(Mamal):
    def __init__(self):
        Mamal.__init__(self)

class Snake(Reptile):
    def __init__(self):
        Reptile.__init__(self)

class Lizard(Reptile):
    def __init__(self):
        Reptile.__init__(self)