import pyservoce.libservoce

class Transform:
	def __init__(self, trans):
		self.trans = trans

	def native(self):
		return self.trans

	def invert(self):
		return Transform(self.trans.invert())

	def __call__(self, obj):
		return obj.transform(self)

	def __mul__(self, oth):
		if isinstance(oth, Transform):
			return Transform(self.trans * oth.trans)
		else:
			raise Exception("Unresolved transform combination type")

	def __str__(self):
		return "transform({}, {})".format(str(self.trans.translation_part()), str(self.trans.rotation_part()))

class Transformable:
	def rotate(self, ax, angle): return pyservoce.trans.rotate(ax, angle)(self)
	def rotateX(self, angle): return pyservoce.trans.rotateX(angle)(self)
	def rotateY(self, angle): return pyservoce.trans.rotateY(angle)(self)
	def rotateZ(self, angle): return pyservoce.trans.rotateZ(angle)(self)

	def translate(self, x, y, z): return pyservoce.trans.translate(x, y, z)(self)
	def up(self, z): 	return pyservoce.trans.up(z)(self)
	def down(self, z): 	return pyservoce.trans.down(z)(self)
	def left(self, x): 	return pyservoce.trans.left(x)(self)
	def right(self, x): return pyservoce.trans.right(x)(self)
	def forw(self, y): 	return pyservoce.trans.forw(y)(self)
	def back(self, y): 	return pyservoce.trans.back(y)(self)

	def mirrorX(self): return pyservoce.trans.mirrorX()(self)
	def mirrorY(self): return pyservoce.trans.mirrorY()(self)
	def mirrorZ(self): return pyservoce.trans.mirrorZ()(self)
	def mirrorXY(self): return pyservoce.trans.mirrorXY()(self)
	def mirrorYZ(self): return pyservoce.trans.mirrorYZ()(self)
	def mirrorXZ(self): return pyservoce.trans.mirrorXZ()(self)

	def transform(self, trans):
		raise Exception("Unimplemented transform method")


def translate(x, y, z): return Transform(pyservoce.libservoce.translate(x,y,z)) 
def right(x): return Transform(pyservoce.libservoce.right(x))
def left(x): return Transform(pyservoce.libservoce.left(x))
def forw(y): return Transform(pyservoce.libservoce.forw(y))
def back(y): return Transform(pyservoce.libservoce.back(y))
def up(z): return Transform(pyservoce.libservoce.up(z))
def down(z): return Transform(pyservoce.libservoce.down(z))

def rotate(ax, angle): return Transform(pyservoce.libservoce.rotate(ax, angle))
def rotateX(angle): return Transform(pyservoce.libservoce.rotateX(angle))
def rotateY(angle): return Transform(pyservoce.libservoce.rotateY(angle))
def rotateZ(angle): return Transform(pyservoce.libservoce.rotateZ(angle))

def mirrorX(): return Transform(pyservoce.libservoce.mirrorX())
def mirrorY(): return Transform(pyservoce.libservoce.mirrorY())
def mirrorZ(): return Transform(pyservoce.libservoce.mirrorZ())

def mirrorXY(): return Transform(pyservoce.libservoce.mirrorXY())
def mirrorYZ(): return Transform(pyservoce.libservoce.mirrorYZ())
def mirrorXZ(): return Transform(pyservoce.libservoce.mirrorXZ())

def nulltrans(): return Transform(pyservoce.libservoce.nulltrans())