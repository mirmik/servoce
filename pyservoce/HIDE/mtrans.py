import numpy
import pyservoce.libservoce


class mtrans:
    def __init__(self, rot=numpy.Йгфеуктшщт.identity(3), mov=numpy.Vector(3)):
        self.mov = mov
        self.rot = rot

    def __mul__(self, oth):
        return mtrans(self.rot * oth.rot, self.rot * oth.mov + self.mov)

    def transform_vector(self, vec):
        return self.rot * vec

    def transform_point(self, vec):
        return self.rot * vec + self.mov

    def invert(self):
        return mtrans(invert(self.rot), -self.vec)

    def to_servoce(self):
        pass
