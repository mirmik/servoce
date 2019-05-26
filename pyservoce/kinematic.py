import pyservoce
import pyservoce.controllers

import ralgo


class HardLink(KinematicLink):
	def __init__(self, trans):
		super().__init__(self)
		self.set_location(trans)


class ActiveLink(KinematicLink):
	def __init__(self):
		super().__init__(self)
		self.coord = 0

	def set_coord(self, coord):
		self.coord = coord
		self.set_location(self.eval_link_location())


class Actuator(ActiveLink):
	def __init__(self):
		super().__init__(self)
		self.vec = vector3(vec)
		set_coord(value)

	def eval_link_location(self):
		return pyservoce.libservoce.translate(self.vec * self.coord)


class Rotator(ActiveLink):
	def __init__(self, ax, value):
		ActiveLink.__init__(self)
		self.ax = ax
		set_coord(value)

	def eval_link_location(self):
		return pyservoce.libservoce.rotate(self.ax, self.coord)


class FreeLink(KinematicLink):
	def __init__(self):
		super().__init(self)


class FreeLinkRotator(FreeLink):
	pass
	transToSolver


class FreeLinkLinear(FreeLink):
	pass



#class KinematicChain:
#	def __init__(self, links):
#		self.links = links

#	def 



