#!/usr/bin/env python3

from wheel.bdist_wheel import bdist_wheel as bdist_wheel_
from setuptools import setup, Extension, Command
from distutils.util import get_platform
import os
import licant

licant.include("nos", "nos/nos.g.py")
licant.include("igris", "igris/igris.g.py")
licant.cxx_objects("nos-objects", 
	mdepends = [
		"nos",
		"igris.include",
	] 
)
nosopts = licant.core.core.get("nos-objects").finalopts

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

liboce_include_path = "/usr/local/include/opencascade"
pyservoce_lib = Extension("pyservoce.libservoce",
	sources = [
		"src/pywrap.cpp",
		"src/surface.cpp",
		"src/curve2.cpp",
		"src/b64.cpp",

		"src/topo.cpp",
		"src/trans.cpp",
		"src/solid.cpp",
		"src/scene.cpp",
		"src/face.cpp",
		"src/wire.cpp",
		"src/boolops.cpp",
		"src/geombase.cpp",
		
		"src/convert.cpp",
		"src/view.cpp",
		"src/camera.cpp",
	] + nosopts["sources"],
	extra_compile_args=['-fPIC', '-std=c++14', '-DNOTRACE=1'],
	extra_link_args=['-Wl,-rpath,$ORIGIN/libs'],
	include_dirs = [liboce_include_path, "src", "include"] + nosopts["include_paths"],
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
	],
)

setup(
	name = 'pyservoce',
	packages = ['pyservoce'],
	version = '1.9.4',
	license='MIT',
	description = 'CAD system for righteous zen programmers ',
	author = 'mirmik',
	author_email = 'mirmikns@yandex.ru',
	url = 'https://mirmik.github.io/zencad/',
	long_description=open("README.md", "r").read(),
	long_description_content_type='text/markdown',
	keywords = ['testing', 'cad'],
	classifiers = [],

	package_data={"pyservoce": "libs/*"},
	include_package_data=True,
	ext_modules = [pyservoce_lib],
	cmdclass = {"bdist_wheel" : bdist_wheel}
)
