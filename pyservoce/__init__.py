import sys
import os

moduledir = os.path.dirname(__file__)
extra_dll_dir = os.path.join(moduledir, "libs")

#print(sys.platform)
#print(extra_dll_dir)

#if (sys.platform == 'win32' or sys.platform == 'win64') and os.path.isdir(extra_dll_dir):
#   os.environ.setdefault('PATH', '')
os.environ['PATH'] += os.pathsep + extra_dll_dir
#  os.environ['PATH'] += os.pathsep + "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\bin"
#   os.environ['PATH'] += os.pathsep + "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib"

from pyservoce.libservoce import *
from pyservoce.controllers import *

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
