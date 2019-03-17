import pyservoce.libservoce
from pyservoce.libservoce import Color

class Scene:
	def __init__(self):
		self.scene = pyservoce.libservoce.Scene()

	def add(self, shp, color=pyservoce.libservoce.Color(0.6, 0.6, 0.8)):	
		if isinstance(shp, pyservoce.point3):
			shp = shp.native()

		if isinstance(shp, pyservoce.Shape):
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
		return View(self.viewer.create_view())

	def clean_context(self):
		return self.viewer.clean_context()

	def add_scene(self, scn):
		return self.viewer.add_scene(scn.native())

	def set_triedron_axes(self):
		self.viewer.set_triedron_axes()


class View:
	def __init__(self, view):
		self.view = view

	def set_triedron(self):
		self.view.set_triedron()

	def set_window(self, idx):
		self.view.set_window(idx)

	def set_gradient(self):
		self.view.set_gradient()

	def set_direction(self, *args):
		self.view.set_direction(*args)

	def set_orthogonal(self):
		self.view.set_orthogonal()

	def redraw(self):
		self.view.redraw()

	def must_be_resized(self):
		self.view.must_be_resized()

	def fit_all(self, arg):
		self.view.fit_all(arg)


