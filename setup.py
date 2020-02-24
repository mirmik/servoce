#!/usr/bin/env python3

from wheel.bdist_wheel import bdist_wheel as bdist_wheel_
from distutils.command.build_ext import build_ext as build_ext_
from setuptools import setup, Extension, Command
from distutils.util import get_platform
import sys
import os
import io
import subprocess

def get_occt_include_directory():
	dirs = ["/usr/include/", "/usr/local/include/"]
	subdirs = ["occt", "opencascade"]

	for d in dirs:
		if os.path.exists(d):
			for f in subdirs:
				fp = os.path.join(d, f)
				if os.path.exists(fp):
					print("OpenCascade Headers directory:", fp)
					return fp 

	raise Exception("can't find occt")


if os.name == "posix":
	liboce_include_path = get_occt_include_directory()
	lib_prefix = ""

elif os.name == "nt":
	liboce_include_path = "C:\\OpenCASCADE-7.3.0-vc14-64/opencascade-7.3.0/inc"
	lib_prefix = "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\"

if sys.platform=="win32" or sys.platform=="win64":
	extra_link_args = []
else:
	extra_link_args = ["-Wl,-rpath,$ORIGIN/libs"]

if sys.platform == "darwin":
	extra_link_args = ["-Wl,-rpath,@loader_path/libs"]	


class build_ext(build_ext_):
	def build_extensions(self):
		ext = self.extensions[0]
		super().build_extensions()
		lst = os.listdir(os.path.join(self.build_lib, "pyservoce"))
		lib = [ f for f in lst if "libservoce" in f ][0]
		print("Builded library path:", lib)

		if sys.platform == "darwin":
			self.darwin_correct_libpathes(os.path.join(self.build_lib, "pyservoce", lib))

	def darwin_correct_libpathes(self, lib):
		print("Correct library pathes for:", lib)
		otool_l = subprocess.Popen(f'otool -L {lib}', shell=True, stdout=subprocess.PIPE)
		otool_l = io.TextIOWrapper(otool_l.stdout).read()
		
		strs = otool_l.split("\n")
		print(otool_l)

		fstrs = []
		for s in strs:
			if "libTK" in s:
				fstrs.append(s.strip().split(" ")[0])

		for f in fstrs:
			#filter parasite dirs addition, f.e. last @rpath addition 
			libname = [ l for l in f.split("/") if "dylib" in l ][0]
			cmd = f"install_name_tool -change {f} @rpath/{libname} {lib}"
			print(cmd)
			os.system(cmd)

class bdist_wheel(bdist_wheel_):
	def finalize_options(self):
		from sys import platform as _platform

		platform_name = get_platform()

		if _platform == "linux" or _platform == "linux2":
			# Linux
			if platform_name == "linux-i686":
				platform_name = "manylinux1_i686"
			else:
				platform_name = "manylinux1_x86_64"

		bdist_wheel_.finalize_options(self)
		self.universal = True
		self.plat_name_supplied = True
		self.plat_name = platform_name

pyservoce_lib = Extension(
	"pyservoce.libservoce",
	sources= [
		"src/pywrap.cpp",
		"src/geombase_py.cpp",
		"src/color_py.cpp",
		"src/surface.cpp",
		"src/curve2.cpp",
		"src/curve3.cpp",
		"src/b64.cpp",
		"src/topo.cpp",
		"src/trans.cpp",
		"src/solid.cpp",
		"src/face.cpp",
		"src/wire.cpp",
		"src/edge.cpp",
		"src/boolops.cpp",
		"src/geombase.cpp",
		"src/boundbox.cpp",
		"src/convert.cpp",
		"src/view.cpp",
		"src/scene.cpp",
		"src/geomprops.cpp",
		"src/viewer.cpp",
		"src/shape_view.cpp",
		"src/camera.cpp",
		"src/prs3d.cpp",
		"src/interactive_object.cpp",
		"src/opencascade_types.cpp",
	],
	extra_compile_args=["-fPIC", "-std=c++14"],
	extra_link_args=extra_link_args,
	include_dirs=[liboce_include_path, "src", "include"],
	#library_dir=["C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib"],
	libraries=[
		lib_prefix + "TKernel",
		lib_prefix + "TKMath",
		lib_prefix + "TKG2d",
		lib_prefix + "TKG3d",
		lib_prefix + "TKBRep",
		lib_prefix + "TKGeomBase",
		lib_prefix + "TKGeomAlgo",
		lib_prefix + "TKTopAlgo",
		lib_prefix + "TKPrim",
		lib_prefix + "TKBO",
		lib_prefix + "TKBool",
		lib_prefix + "TKOffset",
		lib_prefix + "TKService",
		lib_prefix + "TKV3d",
		lib_prefix + "TKOpenGl",
		lib_prefix + "TKFillet",
		lib_prefix + "TKSTL",
		lib_prefix + "TKBin",
		lib_prefix + "TKShHealing",
		lib_prefix + "TKMesh",
		lib_prefix + "TKHLR"
	],
)

setup(
	name="pyservoce",
	packages=["pyservoce"],
	version="1.18.0",
	license="MIT",
	description="CAD system for righteous zen programmers ",
	author="mirmik",
	author_email="mirmikns@yandex.ru",
	url="https://github.com/mirmik/servoce",
	long_description=open("README.md", "r").read(),
	long_description_content_type="text/markdown",
	keywords=["testing", "cad"],
	classifiers=[],
	package_data={"pyservoce": ["libs\\*"]},
	include_package_data=True,
	ext_modules=[pyservoce_lib],
	cmdclass={"bdist_wheel": bdist_wheel, "build_ext": build_ext},
)
