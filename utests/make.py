#!/usr/bin/env python3

import licant
from licant.cxx_modules import application
from licant.modules import submodule, module
from licant.libs import include

licant.include("igris")
licant.include("nos")
licant.include("servoce")

liboce_include_path = "/usr/local/include/opencascade/"

tests = [
	"curve3",
    "solid",
    "face",
    "wire",
    "trans"
]

tests_c = [
]

lib_prefix = ""

application("runtests",
	sources = (
		["main.cpp"] 
		+ [t+".cpp" for t in tests] 
		+ [t+".c" for t in tests_c]),

	ld_flags = "-L/usr/local/lib/",

	include_paths = [".", liboce_include_path],
	mdepends = [
		"igris",
		#"servoce_sources"
	],


	libs = ["gtest", "pthread",
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
        lib_prefix + "TKHLR",
        "X11",
        "servoce"
    ]
)

licant.ex("runtests")