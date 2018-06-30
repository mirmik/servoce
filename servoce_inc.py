#!/usr/bin/env python3
#coding: utf-8

import licant
from licant.cxx_modules import shared_library
from licant.modules import module, submodule

import licant.libs
import os

licant.libs.include("gxx")

libqt_include_path = "/usr/include/x86_64-linux-gnu/qt5/"
liboce_include_path = "/usr/include/oce/"
python_include_prefix = "/usr/include/"

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

module('servoce_sources', 
	srcdir = "src",
	
	sources = [
		"math3.cpp",
		"topo.cpp",
		"trans.cpp",
		"solid.cpp",
		"face.cpp",
		"wire.cpp",
		"boolops.cpp",
		"display.cpp",
		#"test.cpp",
		"convert.cpp",
		"view.cpp",

		"display/mainwidget.cpp",
		"display/dispwidget.cpp",
		"display/dispwidget_qt.cpp",
		"display/icons.cpp",
	],
	
	moc = ["local/display.h"],  
	
	include_paths = [ "include", ".", "src" ],
	
	include_modules = [
		submodule("liboce"), 
		submodule("libqt"), 
		submodule("gxx.include"),
		submodule("gxx", "posix"),
		submodule("gxx.print", "cout"),
		submodule("gxx.dprint", "cout"),
	],
	
	cxx_flags = '-fPIC -DQT_NO_VERSION_TAGGING',
	
	cc_flags = '-fPIC',
)

