import pyservoce.libservoce
import pyservoce.trans
from pyservoce.pntvec import point3

class Shape(pyservoce.trans.Transformable):
	def __init__(self, shape):
		self.shape = shape

	def native(self):
		return self.shape

	def transform(self, trans):
		return Shape(trans.native()(self.native())) 

	def center(self): return point3(self.shape.center())

	def vertices(self) : return [point3(p) for p in self.shape.vertices()]
	
	def fill(self): fill(self)

	def __add__(self, oth): return Shape(self.native() + oth.native())
	def __sub__(self, oth): return Shape(self.native() - oth.native())
	def __xor__(self, oth): return Shape(self.native() ^ oth.native())

	def shapetype(self):
		return self.shape.shapetype()

#prim3d
def box(*args, **kwargs): return Shape(pyservoce.libservoce.box(*args, **kwargs))
def sphere(*args, **kwargs): return Shape(pyservoce.libservoce.sphere(*args, **kwargs))
def cylinder(*args): return Shape(pyservoce.libservoce.cylinder(*args))
def cone(r1, r2, h, center = False, yaw=None): 
	if yaw is None:
		return Shape(pyservoce.libservoce.cone(r1,r2,h,center=center))
	else:
		return Shape(pyservoce.libservoce.cone(r1,r2,h,0,yaw,center=center))
def torus(*args): return Shape(pyservoce.libservoce.torus(*args))
def halfspace(*args): return Shape(pyservoce.libservoce.halfspace(*args))

#prim2d
def rectangle(a, b, center=False, wire=False): return Shape(pyservoce.libservoce.rectangle(a, b, center=center, wire=wire))
def square(a, center=False, wire=False): return Shape(pyservoce.libservoce.square(a, center=center, wire=wire))
def circle(r, wire=False): return Shape(pyservoce.libservoce.circle(r=r, wire=wire))
def textshape(*args, **kwargs): return Shape(pyservoce.libservoce.textshape(*args, **kwargs))
def polygon(pnts): return Shape(pyservoce.libservoce.polygon([p.native() for p in pnts]))
def ngon(r, n, wire=False): return Shape(pyservoce.libservoce.ngon(r=r, n=n, wire=wire))

#prim1d
def segment(a, b): return Shape(pyservoce.libservoce.segment(a.native(), b.native()))
def circle_arc(a, b, c): return Shape(pyservoce.libservoce.circle_arc(a.native(), b.native(), c.native()))
def polysegment(pnts, closed=False): return Shape(pyservoce.libservoce.polysegment([p.native() for p in pnts], closed))
def interpolate(pnts, tang, closed): return Shape(pyservoce.libservoce.interpolate([p.native() for p in pnts], [t.native() for t in tang], closed))
def long_helix(radius, height, step, angle, leftHanded): return Shape(pyservoce.libservoce.long_helix(radius=radius, height=height, step=step, angle=angle, leftHanded=leftHanded))

#ops1d2d
def sew(wires): return Shape(pyservoce.libservoce.sew([w.native() for w in wires]))
def fill(shp): return Shape(pyservoce.libservoce.fill(shp))

#ops3d
def loft(arr, smooth):
	return Shape(pyservoce.libservoce.loft([a.native() for a in arr], smooth))

def pipe_shell(prof, traj, freenet):
	return Shape(pyservoce.libservoce.make_pipe_shell(prof.native(), traj.native(), freenet))

def linear_extrude(shp, vec, center): 
	return Shape(pyservoce.libservoce.make_linear_extrude(shp.native(), vec.native(), center))

def fillet(shp, r, refs=None):
	if refs is None:
		return Shape(pyservoce.libservoce.fillet(shp.native(), r))
	return Shape(pyservoce.libservoce.fillet(shp.native(), r, [p.native() for p in refs]))

def chamfer(shp, r, refs=None):
	if refs is None:
		return Shape(pyservoce.libservoce.chamfer(shp, r))
	return Shape(pyservoce.libservoce.chamfer(shp.native(), r, [p.native() for p in refs]))

def thicksolid(shp, refs, t):
	return Shape(pyservoce.libservoce.thicksolid(shp.native(), [p.native() for p in refs], t))