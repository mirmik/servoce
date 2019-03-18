import pyservoce.libservoce
import pyservoce.trans
from pyservoce.pntvec import point3

class Shape:
	def __init__(self, shape):
		self.shape = shape

	def native(self):
		return self.shape

	def transform(self, trans):
		return Shape(trans.native()(self.native())) 

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