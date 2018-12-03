#!/usr/bin/env python3
#coding: utf-8

import licant
from licant.cxx_modules import shared_library
from licant.modules import module, submodule

import licant.libs
import os

full_list = [
	'TKBinL',
	'TKBin',
	'TKBinTObj',
	'TKBinXCAF',
	'TKBool',
	'TKBO',
	'TKBRep',
	'TKCAF ',
	'TKCDF ',
	'TKDCAF',
	'TKDraw',
	'TKernel',
	'TKFeat',
	'TKFillet',
	'TKG2d',
	'TKG3d',
	'TKGeomAlgo',
	'TKGeomBase',
	'TKHLR',
	'TKIGES',
	'TKLCAF',
	'TKMath',
	'TKMesh',
	'TKMeshVS',
	'TKOffset',
	'TKOpenGl',
	'TKPrim',
	'TKQADraw',
	'TKService',
	'TKShHealing ',
	'TKStdL',
	'TKStd ',
	'TKSTEP209 ',
	'TKSTEPAttr',
	'TKSTEPBase',
	'TKSTEP',
	'TKSTL',
	'TKTObjDRAW',
	'TKTObj',
	'TKTopAlgo',
	'TKTopTest',
	'TKV3d',
	'TKVCAF',
	'TKViewerTest',
	'TKVRML',
	'TKXCAF',
	'TKXCAF',
	'TKXDEDRAW',
	'TKXDEIGES',
	'TKXDESTEP',
	'TKXMesh',
	'TKXmlL',
	'TKXml',
	'TKXmlTObj',
	'TKXmlXCAF',
	'TKXSBase',
	'TKXSDRAW',
]

licant.libs.include("gxx")

class Found(Exception): pass
try:
	for root, dirs, files in os.walk("/usr/include"):
		for dr in dirs:
			if dr == "qt5":
				libqt_include_path = os.path.join(root, dr)
				raise Found()
	else:
		print("NeedInstall Qt5")
		exit(-1)
except (Found):
	pass

#liboce_include_path = "/usr/include/oce/"
liboce_include_path = "/usr/local/include/opencascade"
python_include_prefix = "/usr/include/"

module('liboce', 
	libs = [
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
		"scene.cpp",
		"geombase.cpp",
		"view.cpp",
		"camera.cpp",

		"display/mainwidget.cpp",
		"display/dispwidget.cpp",
		"display/dispwidget_qt.cpp",
		"display/icons.cpp",

#		"shower/mainwidget.cpp",
#		"shower/dispwidget.cpp",
#		"shower/dispwidget_qt.cpp",

#		"occversion.cpp",

		#"widgets/gtk_widget.cpp"
	],
	
	moc = ["local/display.h"],
	
	include_paths = [ "include", ".", "src" ],
	
	include_modules = [
		submodule("liboce"), 
		submodule("libqt"), 
#		submodule("gxx.include"),
#		submodule("gxx", "posix"),
#		submodule("gxx.print", "cout"),
#		submodule("gxx.dprint", "cout"),
	],

	libs = ['X11'],
	
	cxx_flags = '-Wall -fPIC -DQT_NO_VERSION_TAGGING -ffunction-sections -fdata-sections',
	cc_flags = '-Wall -fPIC -ffunction-sections -fdata-sections',
	ld_flags = '-ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--as-needed'
)

