import sys
import os

moduledir = os.path.dirname(__file__)
extra_dll_dir = os.path.join(moduledir, "libs")

#print(sys.platform)
#print(extra_dll_dir)

#if (sys.platform == 'win32' or sys.platform == 'win64') and os.path.isdir(extra_dll_dir):
#   os.environ.setdefault('PATH', '')
if sys.platform == "win32" or sys.platform == "win64":
    os.environ['PATH'] += os.pathsep + extra_dll_dir + os.pathsep + moduledir
#  os.environ['PATH'] += os.pathsep + "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\bin"
#   os.environ['PATH'] += os.pathsep + "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib"

import pyservoce.libservoce
from pyservoce.libservoce import *

# Patch Scene object to suport display python objects.
Raw_Scene_add = pyservoce.libservoce.Scene.add

default_color = (0.6, 0.6, 0.8)

def Scene_add(scene, obj, color=default_color):
    if not isinstance(color, pyservoce.libservoce.Color):
        color = pyservoce.libservoce.Color(*color)

    if (
    	   isinstance(obj, pyservoce.libservoce.Shape) 
    	or isinstance(obj, pyservoce.libservoce.point3)
    ):
        return Raw_Scene_add(scene, obj, color)
    elif isinstance(obj, pyservoce.libservoce.interactive_object):
        return Raw_Scene_add(scene, obj)
    else:
        return obj.bind_to_scene(scene, color)


color = pyservoce.libservoce.Color
pyservoce.libservoce.Scene.add = Scene_add


pyservoce.libservoce.transformation.__call__ = lambda self, obj: obj.transform(self)

class TransformableMixin:
    def transform(self, trsf):
        raise Exception("transform not implemented")

    def translate(self, *args, **kwargs): return self.transform(translate(*args,**kwargs))
    def move(self, *args, **kwargs): return self.transform(move(*args,**kwargs))
    def moveX(self, *args, **kwargs): return self.transform(moveX(*args,**kwargs))
    def moveY(self, *args, **kwargs): return self.transform(moveY(*args,**kwargs))
    def moveZ(self, *args, **kwargs): return self.transform(moveZ(*args,**kwargs))
    def movX(self, *args, **kwargs): return self.transform(moveX(*args,**kwargs))
    def movY(self, *args, **kwargs): return self.transform(moveY(*args,**kwargs))
    def movZ(self, *args, **kwargs): return self.transform(moveZ(*args,**kwargs))

    def up(self, *args, **kwargs): return self.transform(up(*args,**kwargs))
    def down(self, *args, **kwargs): return self.transform(down(*args,**kwargs))
    def left(self, *args, **kwargs): return self.transform(left(*args,**kwargs))
    def right(self, *args, **kwargs): return self.transform(right(*args,**kwargs))
    def forw(self, *args, **kwargs): return self.transform(forw(*args,**kwargs))
    def back(self, *args, **kwargs): return self.transform(back(*args,**kwargs))

    def rotate(self, *args, **kwargs): return self.transform(rotate(*args,**kwargs))
    def rotateX(self, *args, **kwargs): return self.transform(rotateX(*args,**kwargs))
    def rotateY(self, *args, **kwargs): return self.transform(rotateY(*args,**kwargs))
    def rotateZ(self, *args, **kwargs): return self.transform(rotateZ(*args,**kwargs))

    def rotX(self, *args, **kwargs): return self.transform(rotateX(*args,**kwargs))
    def rotY(self, *args, **kwargs): return self.transform(rotateY(*args,**kwargs))
    def rotZ(self, *args, **kwargs): return self.transform(rotateZ(*args,**kwargs))

    def mirrorO(self, *args, **kwargs): return self.transform(mirrorO(*args,**kwargs))
    def mirrorX(self, *args, **kwargs): return self.transform(mirrorX(*args,**kwargs))
    def mirrorY(self, *args, **kwargs): return self.transform(mirrorY(*args,**kwargs))
    def mirrorZ(self, *args, **kwargs): return self.transform(mirrorZ(*args,**kwargs))
    def mirrorXY(self, *args, **kwargs): return self.transform(mirrorXY(*args,**kwargs))
    def mirrorYZ(self, *args, **kwargs): return self.transform(mirrorYZ(*args,**kwargs))
    def mirrorXZ(self, *args, **kwargs): return self.transform(mirrorXZ(*args,**kwargs))

    def scale(self, *args, **kwargs): return self.transform(scale(*args,**kwargs))




def curve_parameters(self):
    print("curve_parameters")

    if self.curvetype() == "line":
        pass









