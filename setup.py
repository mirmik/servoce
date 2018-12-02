#!/usr/bin/env python3

from wheel.bdist_wheel import bdist_wheel as bdist_wheel_
from setuptools import setup, Extension, Command
from distutils.util import get_platform
import os

class bdist_wheel(bdist_wheel_):
	def finalize_options(self):
		from sys import platform as _platform
		platform_name = get_platform()

		if _platform == "linux" or _platform == "linux2":
			# Linux
			if platform_name == "linux-i686":
				platform_name = 'manylinux1_i686'
			else:
				platform_name = 'manylinux1_x86_64'
			
		bdist_wheel_.finalize_options(self)
		self.universal = True
		self.plat_name_supplied = True
		self.plat_name = platform_name


#class Found(Exception): pass
#try:
#	for root, dirs, files in os.walk("/usr/include"):
#		for dr in dirs:
#			if dr == "qt5":
#				libqt_include_path = os.path.join(root, dr)
#				raise Found()
#	else:
#		print("NeedInstall Qt5")
#		exit(-1)
#except (Found):
#	pass


liboce_include_path = "/usr/local/include/opencascade"

pyservoce_lib = Extension("pyservoce.libservoce",
	sources = [
		"src/pywrap.cpp",
		"src/b64.cpp",

		"src/math3.cpp",
		"src/topo.cpp",
		"src/trans.cpp",
		"src/solid.cpp",
		"src/face.cpp",
		"src/wire.cpp",
		"src/boolops.cpp",
		"src/geombase.cpp",
		#"src/display.cpp",
		
		"src/convert.cpp",
		"src/view.cpp",
		"src/camera.cpp",

#		"src/display/mainwidget.cpp",
#		"src/display/dispwidget.cpp",
#		"src/display/dispwidget_qt.cpp",
#		"src/local/display_h_moc.cpp",
#		"src/display/icons.cpp",

#		"src/shower/mainwidget.cpp",
#		"src/shower/dispwidget.cpp",
#		"src/shower/dispwidget_qt.cpp",
#		"src/local/shower_h_moc.cpp",
	],
	extra_compile_args=['-fPIC', '-std=c++14'],
	#extra_link_args=['-Wl,-rpath,\'$ORIGIN/libs/\''],
	extra_link_args=['-Wl,-rpath,$ORIGIN/libs'],
	#extra_link_args=['-Wl,-rpath,./libs'],
	include_dirs = [liboce_include_path, "src", "include"],
	libraries = [
		'TKernel',
		'TKMath',
		'TKG2d',
		'TKG3d',
		'TKBRep',
		'TKGeomBase',
		'TKGeomAlgo',
		'TKTopAlgo',
		'TKPrim',
		'TKBO',
		'TKBool',
		'TKOffset',
		'TKService',
		'TKV3d',
		'TKOpenGl',
		'TKFillet',
		'TKSTL',
		'TKBin',
		'TKShHealing',
		'TKMesh',
		'TKHLR',
		
		#'Qt5Core', 
		#'Qt5Widgets', 
		#'Qt5Test', 
		#'Qt5Gui', 
		#'Qt5OpenGL',
	],
)

setup(
	name = 'pyservoce',
	packages = ['pyservoce'],
	version = '1.4.0',
	license='MIT',
	description = 'CAD system for righteous zen programmers ',
	author = 'Sorokin Nikolay',
	author_email = 'mirmikns@yandex.ru',
	url = 'https://mirmik.github.io/zencad/',
	keywords = ['testing', 'cad'],
	classifiers = [],

	include_package_data=True,
	ext_modules = [pyservoce_lib],
	cmdclass = {"bdist_wheel" : bdist_wheel}
)
