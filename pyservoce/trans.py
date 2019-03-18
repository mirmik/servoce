import pyservoce.libservoce

class Transform:
	def __init__(self, trans):
		self.trans = trans

	def invert():
		return Transform(self.trans.invert())

	def __call__(self, obj):
		return obj.transform(self)

	def __mul__(self, oth):
		if isinstance(oth, Transform):
			return Transform(self.trans * oth.trans)
		else:
			raise Exception("Unresolved transform combination type")


def translate(x, y, z): return Transform(pyservoce.libservoce.translate(x,y,z)) 
def right(x): return Transform(pyservoce.libservoce.right(x))
def left(x): return Transform(pyservoce.libservoce.left(x))
def forw(y): return Transform(pyservoce.libservoce.forw(y))
def back(y): return Transform(pyservoce.libservoce.back(y))
def up(z): return Transform(pyservoce.libservoce.up(z))
def down(z): return Transform(pyservoce.libservoce.down(z))

def rotate(ax, angle): Transform(pyservoce.libservoce.rotate(ax, angle))
def rotateX(angle): Transform(pyservoce.libservoce.rotateX(angle))
def rotateY(angle): Transform(pyservoce.libservoce.rotateY(angle))
def rotateZ(angle): Transform(pyservoce.libservoce.rotateZ(angle))

def mirrorX(): Transform(pyservoce.libservoce.mirrorX())
def mirrorY(): Transform(pyservoce.libservoce.mirrorY())
def mirrorZ(): Transform(pyservoce.libservoce.mirrorZ())

def mirrorXY(): Transform(pyservoce.libservoce.mirrorXY())
def mirrorYZ(): Transform(pyservoce.libservoce.mirrorYZ())
def mirrorXZ(): Transform(pyservoce.libservoce.mirrorXZ())