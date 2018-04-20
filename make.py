#!/usr/bin/env python3
#coding: utf-8

import licant
from licant.cxx_modules import shared_library
from licant.modules import module

import licant.libs
import os

licant.libs.include("gxx")

libqt_include_path = "/usr/include/x86_64-linux-gnu/qt5/"
liboce_include_path = "/usr/include/oce"
python_include_prefix = "/usr/include/"

install_lib_dir = "/usr/lib/"
install_inc_dir = "/usr/local/include/"

module('liboce', 
	libs = [     
		'TKernel',
		'TKMath',
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
	],
	include_paths = [liboce_include_path]    
)

module('libqt', 
	libs = [    
		'Qt5Core', 
		'Qt5Widgets', 
		'Qt5Test', 
		'Qt5Gui', 
		'Qt5OpenGL',
	],
	include_paths = [libqt_include_path]    
)

shared_library("libservoce.so", 
	srcdir = "src",

	sources = [
		"math3.cpp",
		"topo.cpp",
		"solid.cpp",
		"face.cpp",
		"wire.cpp",
		"boolops.cpp",
		"display.cpp",

		"display/mainwidget.cpp",
		"display/dispwidget.cpp",
	],

	moc = ["local/display.h"],  

	include_paths = [ "include", ".", "src" ],
	include_modules = ["liboce", "libqt", "gxx.include",
		("gxx", "posix"),
		("gxx.print", "cout"),
		("gxx.dprint", "cout"),
	],

	cxx_flags = '-fPIC -DQT_NO_VERSION_TAGGING',
	cc_flags = '-fPIC',
)

@licant.routine
def install():
	licant.make.copy(src="libservoce.so", tgt=install_lib_dir+"libservoce.so")
	licant.do(install_lib_dir+"libservoce.so")
	os.system("cp -r include/servoce {}".format(install_inc_dir))

licant.ex(default = "libservoce.so")
