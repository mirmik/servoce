import pyservoce.libservoce
from pyservoce.pntvec import point3

class Shape:
	def __init__(self, shape):
		self.shape = shape

	def native(self):
		return self.shape

	def rotate(self, ax, angle): return Shape(self.shape.rotate(ax, angle))
	def rotateX(self, angle): return Shape(self.shape.rotateX(angle))
	def rotateY(self, angle): return Shape(self.shape.rotateY(angle))
	def rotateZ(self, angle): return Shape(self.shape.rotateZ(angle))

	def translate(self, x, y, z): return Shape(self.shape.translate(x, y, z))
	def up(self, z): return Shape(self.shape.up(z))
	def down(self, z): return Shape(self.shape.down(z))
	def left(self, z): return Shape(self.shape.left(z))
	def right(self, z): return Shape(self.shape.right(z))
	def forw(self, z): return Shape(self.shape.forw(z))
	def back(self, z): return Shape(self.shape.back(z))

	def mirrorX(self): return Shape(self.shape.mirrorX())
	def mirrorY(self): return Shape(self.shape.mirrorY())
	def mirrorZ(self): return Shape(self.shape.mirrorZ())
	def mirrorXY(self): return Shape(self.shape.mirrorXY())
	def mirrorYZ(self): return Shape(self.shape.mirrorYZ())
	def mirrorXZ(self): return Shape(self.shape.mirrorXZ())

	def center(self): return point3(self.shape.center())
	
	def fill(self): fill(self)

	def __add__(self, oth): return Shape(self.native() + oth.native())
	def __sub__(self, oth): return Shape(self.native() - oth.native())
	def __xor__(self, oth): return Shape(self.native() ^ oth.native())

#prim3d
def box(*args): return Shape(pyservoce.libservoce.box(*args))
def sphere(*args): return Shape(pyservoce.libservoce.sphere(*args))
def cylinder(*args): return Shape(pyservoce.libservoce.torus(*args))
def cone(*args): return Shape(pyservoce.libservoce.cone(*args))
def torus(*args): return Shape(pyservoce.libservoce.torus(*args))
def halfspace(*args): return Shape(pyservoce.libservoce.halfspace(*args))

#prim2d
def textshape(*args): return Shape(pyservoce.libservoce.textshape(*args))

#prim1d
def sew(wires): return Shape(pyservoce.libservoce.sew([w.native() for w in wires]))
def fill(shp): return Shape(pyservoce.libservoce.fill(shp))

def interpolate(pnts, tang, closed):
	return Shape(pyservoce.libservoce.interpolate([p.native() for p in pnts], [t.native() for t in tang], closed))

def polygon(pnts):
	return Shape(pyservoce.libservoce.polygon([p.native() for p in pnts]))

def polysegment(pnts, closed=False):
	return Shape(pyservoce.libservoce.polysegment([p.native() for p in pnts], closed))

def segment(a, b):
	return Shape(pyservoce.libservoce.segment(a.native(), b.native()))

def circle_arc(a, b, c):
	return Shape(pyservoce.libservoce.circle_arc(a.native(), b.native(), c.native()))

def make_linear_extrude(shp, vec, center):
	return Shape(pyservoce.libservoce.make_linear_extrude(shp, vec.native(), center))

def fillet(shp, r, refs=None):
	if refs is None:
		return Shape(pyservoce.libservoce.fillet(shp, r))
	return Shape(pyservoce.libservoce.fillet(shp, r, [p.native() for p in refs]))

def chamfer(shp, r, refs=None):
	if refs is None:
		return Shape(pyservoce.libservoce.chamfer(shp, r))
	return Shape(pyservoce.libservoce.chamfer(shp, r, [p.native() for p in refs]))

def thicksolid(shp, refs, t):
	return Shape(pyservoce.libservoce.thicksolid(shp, [p.native() for p in refs], t))