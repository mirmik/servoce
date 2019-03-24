import pyservoce.libservoce
from pyservoce.libservoce import Color

import pyservoce.trans
import pyservoce.controllers
from pyservoce.defs import *

class UnresolvedViewedType(Exception):
    def __init__(self, expression):
        self.expression = expression

class Scene:
	class Viewer:
		def __init__(self, scn=None):
			if scn is None:
				self.viewer = pyservoce.libservoce.Viewer()
			else:
				self.viewer = pyservoce.libservoce.Viewer(scn.native())
	
		def create_view(self):
			return View(self.viewer.create_view())
	
		def clean_context(self):
			return self.viewer.clean_context()
	
		def add_scene(self, scn):
			return self.viewer.add_scene(scn.native())
	
		def set_triedron_axes(self):
			self.viewer.set_triedron_axes()

		def display(self, ctr):
			self.viewer.display(ctr)

	def __init__(self):
		self.scene = pyservoce.libservoce.Scene()
		self.viewer = self.Viewer(self)

	def add(self, shp, color=None):	
		if isinstance(shp, pyservoce.point3):
			shp = shp.vertex()

		if isinstance(shp, pyservoce.Shape):
			controller = pyservoce.controllers.ShapeController(shape=shp)
			controller.bind_to_scene(self, color)
			return controller

		elif isinstance(shp, pyservoce.controllers.Unit):
			shp.bind_to_scene(self, color)
			return shp

		raise UnresolvedViewedType(shp.__class__)

	def native(self):
		return self.scene



class View:
	def __init__(self, view):
		self.view = view

	def set_triedron(self):
		self.view.set_triedron()

	def set_window(self, idx):
		self.view.set_window(idx)

	def set_virtual_window(self,w,h):
		self.view.set_virtual_window(w,h)

	def set_gradient(self):
		self.view.set_gradient()

	def set_direction(self, *args):
		self.view.set_direction(*args)

	def set_orthogonal(self):
		self.view.set_orthogonal()

	def rawarray(self, w, h):
		return self.view.rawarray(w, h)

	def redraw(self):
		self.view.redraw()

	def must_be_resized(self):
		self.view.must_be_resized()

	def fit_all(self, arg=0.5):
		self.view.fit_all(arg)

	def zoom(self, a, b, c, d):
		self.view.zoom(a, b, c, d)

	def pan(self, a, b):
		self.view.pan(a, b)

	def intersect_point(self, a, b):
		return self.view.intersect_point(a, b)

	def direction(self):
		return self.view.direction()
