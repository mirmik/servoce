import pyservoce
from pyservoce.libservoce import *

class xy:
	def get_x(self):
		return self.arr[0]

	def get_y(self):
		return self.arr[1]

	def set_x(self, x): 
		self.arr[0] = x 

	def set_y(self, y): 
		self.arr[1] = y

	def __iter__(self):
		return iter(self.arr)

	def __getitem__(self, key):
		return self.arr[key]

	def __setitem__(self, key, value):
		self.arr[key] = value

	x = property(get_x, set_x)
	y = property(get_y, set_y)

class xyz(xy):
	def get_z(self):
		return self.arr[2]
	
	def set_z(self, z): 
		self.arr[2] = z

	z = property(get_z, set_z)

class point2(xy):
	def __init__(self, *args):
		if len(args) == 0:
			self.arr = (0, 0, 0)

		if len(args) == 1:
			self.arr = (args[0][0], args[0][1], args[0][2])

		if len(args) == 2:
			self.arr = (args[0], args[1], 0)

	def native(self): return pyservoce.libservoce.point2_native(self.x, self.y)
	def __repr__(self): return "point2({},{})".format(self.arr[0], self.arr[1])
	def __getstate__(self): return self.arr
	def __setstate__(self, obj): self.arr=obj 

class point3(xyz):
	def __init__(self, *args):
		if len(args) == 0:
			self.arr = (0, 0, 0)

		if len(args) == 1:
			self.arr = (args[0][0], args[0][1], args[0][2])

		if len(args) == 2:
			self.arr = (args[0], args[1], 0)

		if len(args) == 3:
			self.arr = (args[0], args[1], args[2])

	def native(self): return pyservoce.libservoce.point3_native(self.arr[0], self.arr[1], self.arr[2])
	def __repr__(self): return "point3({},{},{})".format(self.arr[0], self.arr[1], self.arr[2])
	def __getstate__(self): return self.arr
	def __setstate__(self, obj): self.arr=obj 

class vector3(xyz):
	def __init__(self, *args):
		if len(args) == 0:
			self.arr = (0, 0, 0)

		if len(args) == 1:
			self.arr = (args[0][0], args[0][1], args[0][2])

		if len(args) == 2:
			self.arr = (args[0], args[1], 0)

		if len(args) == 3:
			self.arr = (args[0], args[1], args[2])

	def native(self): return pyservoce.libservoce.vector3_native(self.arr[0], self.arr[1], self.arr[2])
	def __repr__(self): return "vector3({},{},{})".format(self.arr[0], self.arr[1], self.arr[2])
	def __getstate__(self): return self.arr
	def __setstate__(self, obj): self.arr=obj 


class Scene:
	def __init__(self):
		self.scene = pyservoce.libservoce.Scene()

	def add(self, shp, color=pyservoce.libservoce.Color(0.6, 0.6, 0.8)):	
		if isinstance(shp, pyservoce.point3):
			shp = shp.native()

		return self.scene.add(shp, color)

	def native(self):
		return self.scene

class Viewer:
	def __init__(self, scn=None):
		if scn is None:
			self.viewer = pyservoce.libservoce.Viewer()
		else:
			self.viewer = pyservoce.libservoce.Viewer(scn.native())

	def create_view(self):
		return self.viewer.create_view()

	def clean_context(self):
		return self.viewer.clean_context()

	def add_scene(self, scn):
		return self.viewer.add_scene(scn.native())

	def set_triedron_axes(self):
		self.viewer.set_triedron_axes()


def interpolate(pnts, tang, closed):
	return pyservoce.libservoce.interpolate([p.native() for p in pnts], [t.native() for t in tang], closed)

def polygon(pnts):
	return pyservoce.libservoce.polygon([p.native() for p in pnts])

def polysegment(pnts, closed=False):
	return pyservoce.libservoce.polysegment([p.native() for p in pnts], closed)

def segment(a, b):
	return pyservoce.libservoce.segment(a.native(), b.native())

def circle_arc(a, b, c):
	return pyservoce.libservoce.circle_arc(a.native(), b.native(), c.native())

def make_linear_extrude(shp, vec, center):
	return pyservoce.libservoce.make_linear_extrude(shp, vec.native(), center)

def fillet(shp, r, refs=None):
	if refs is None:
		return pyservoce.libservoce.fillet(shp, r)
	return pyservoce.libservoce.fillet(shp, r, [p.native() for p in refs])

def chamfer(shp, r, refs=None):
	if refs is None:
		return pyservoce.libservoce.chamfer(shp, r)
	return pyservoce.libservoce.chamfer(shp, r, [p.native() for p in refs])

def thicksolid(shp, refs, t):
	return pyservoce.libservoce.thicksolid(shp, [p.native() for p in refs], t)