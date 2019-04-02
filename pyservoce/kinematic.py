import pyservoce
import pyservoce.controllers

class ActiveLink(pyservoce.controllers.Assemble):
	pass

class Actuator(ActiveLink):
	pass

class Rotator(ActiveLink):
	pass