from pyservoce.libservoce import *
from pyservoce.controllers import *

#Patch Scene object to suport display python objects.
Raw_Scene_add = pyservoce.libservoce.Scene.add
def Scene_add(scene, obj, color=(0.6,0.6,0.8)):
	if not isinstance(color, pyservoce.libservoce.Color):
		color = pyservoce.libservoce.Color(*color)	

	if isinstance(obj, pyservoce.libservoce.Shape) or isinstance(obj, pyservoce.libservoce.point3):
		return Raw_Scene_add(scene, obj, color)	
	else:
		return obj.bind_to_scene(scene, color)
pyservoce.libservoce.Scene.add = Scene_add 

pyservoce.libservoce.Shape.fillet = lambda *args, **kwargs: pyservoce.fillet(*args, **kwargs)
pyservoce.libservoce.Shape.fillet2d = lambda *args, **kwargs: pyservoce.fillet2d(*args, **kwargs)
pyservoce.libservoce.Shape.chamfer = lambda *args, **kwargs: pyservoce.chamfer(*args, **kwargs)
pyservoce.libservoce.Shape.chamfer2d = lambda *args, **kwargs: pyservoce.chamfer2d(*args, **kwargs)