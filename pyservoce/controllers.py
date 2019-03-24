import pyservoce.trans
from pyservoce.defs import *
from pyservoce.geom import *

import evalcache
from evalcache import LazyObject

class WrongUnitType(Exception): pass

def unlazy_if_need(obj):
	if isinstance(obj, LazyObject):
		return evalcache.unlazy(obj)
	else:
		return obj

def to_unit(obj):
	if isinstance(obj, Shape):
		return ShapeController(obj)

	if not isinstance(obj, Unit):
		raise WrongUnitType

class Unit(pyservoce.trans.Transformable):
	def __init__(self, parent=None, location=pyservoce.trans.nulltrans()):
		self.parent = parent

		if parent is not None:
			parent.add_part(self, location)

		else:
			self.eval_location(location)


	def update_global_location(self):
		if self.local_location is None:
			if self.parent is None:
				self.global_location = pyservoce.nulltrans()
			else:
				self.global_location = self.parent.global_location
			return

		if self.parent is None:
			self.global_location = self.local_location
		else:
			self.global_location = self.parent.global_location * self.local_location

		#if self.parent is not None:
		#	print("g1", self.parent.global_location)
		#print("g2", self.global_location)
		#print("g3", self.local_location)

	def eval_location(self, location):
		if location is None:
			self.local_location = None
		else:
			self.local_location = location.unlazy() if isinstance(location, LazyObject) else location
		self.update_global_location()

	def set_location(self, location):
		self.eval_location(location)
		self.apply_location()

	def apply_location(self):
		raise NotImplementedError()

	def bind_to_scene(self, scene, color):
		raise NotImplementedError()		

	
class Assemble(Unit):
	def __init__(self, parts=None, parent=None, location=pyservoce.trans.nulltrans()):
		Unit.__init__(self, parent, location)
		self.parts = []
		
		if parts is not None:
			for p in parts:
				self.add_part(p)

		self.apply_location()


	def add_part(self, unit, location=pyservoce.trans.nulltrans()):
		unit = unlazy_if_need(unit)

		if isinstance(unit, pyservoce.geom.Shape):
			unit = ShapeController(unit)

		if isinstance(unit, Unit):
			unit.parent = self
			self.parts.append(unit)
			unit.eval_location(location)
			return unit

		raise WrongUnitType()

	def apply_location(self):
		for p in self.parts:
			p.update_global_location()
			p.apply_location()

	def bind_to_scene(self, scene, color=None):
		for p in self.parts:
			p.bind_to_scene(scene, color)

	def set_color(self, *args):
		for p in self.parts:
			p.set_color(*args)


class ShapeView:
	def __init__(self, sctrl):
		self.sctrl = sctrl

	def set_location(self, trans):
		self.sctrl.set_location(trans.native())

	def hide(self, en):
		self.sctrl.hide(en)


class ShapeController(Unit):
	def __init__(self, shape, parent=None, location=None):
		Unit.__init__(self, parent, location)		
		self.shape = shape.unlazy() if isinstance(shape, LazyObject) else shape
		self.views = []
		self.color = None
		self.apply_location()

	def set_color(self, *args):
		if not isinstance(args[0], pyservoce.libservoce.Color):
			color = pyservoce.libservoce.Color(*args)

		self.color = color

	def apply_location(self):
		for v in self.views:
			v.set_location(self.global_location)

	def hide(self, en):
		for v in self.views:
			v.hide(en)

	def bind_to_scene(self, scene, color=None):
		if color is None and self.color is None:
			color = pyservoce.defs.DEFAULT_COLOR

		if self.color is not None:
			color = self.color

		if not isinstance(color, pyservoce.libservoce.Color):
			color = pyservoce.libservoce.Color(*color)


		print(color.r, color.g, color.b)

		shape_view = ShapeView(scene.native().add(self.shape.native(), color))
		scene.viewer.display(shape_view.sctrl)		
		self.views.append(shape_view)

		self.apply_location()


class RotateConnector(Assemble):
	def __init__(self, child=None, parent=None, location=pyservoce.trans.nulltrans()):
		Assemble.__init__(self, parts=[child], parent=parent, location=location)
		self.child = self.parts[0]

