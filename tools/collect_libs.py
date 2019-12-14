#!/usr/bin/env python3
# coding:utf-8

import os
import sys

vers = "7.3.0"

if len(sys.argv) > 1:
	vers = sys.argv[1]

os.system("mkdir -p pyservoce/libs")
iswin = sys.platform == "win32" or sys.platform == "win64"

listlibs = [
	"TKernel",
	"TKMath",
	"TKG2d",
	"TKG3d",
	"TKBRep",
	"TKGeomBase",
	"TKGeomAlgo",
	"TKTopAlgo",
	"TKPrim",
	"TKBO",
	"TKBool",
	"TKOffset",
	"TKService",
	"TKV3d",
	"TKOpenGl",
	"TKFillet",
	"TKSTL",
	"TKBin",
	"TKShHealing",
	"TKMesh",
	"TKHLR",
]

def get_occt_library_directory():
	dirs = ["/usr/local/lib/", "/usr/lib/x86_64-linux-gnu/"]
	
	for d in dirs:
		if "libTKernel.so" in os.listdir(d):
			return d 
	else:
		raise Exception("can't find occt")
occt_libs_dir = get_occt_library_directory()

filelist = os.listdir(occt_libs_dir)

for l in listlibs:
	fl = "lib" + l + ".so.{}".format(vers)
	if fl in filelist:
		f = fl

		cmd0 = "cp {0} pyservoce/libs/".format(os.path.join(occt_libs_dir, f))
		if not iswin:
			cmd05 = "patchelf --set-rpath '$ORIGIN' pyservoce/libs/{0}".format(f)
		cmd1 = "ln -s {2}/pyservoce/libs/{0} {2}/pyservoce/libs/{1}".format(
			f, f[:-4], os.getcwd()
		)
		cmd2 = "ln -s {2}/pyservoce/libs/{0} {2}/pyservoce/libs/{1}".format(
			f, f[:-6], os.getcwd()
		)

		print(cmd0)
		if not iswin:
			print(cmd05)
		print(cmd1)
		print(cmd2)

		os.system(cmd0)
		if not iswin:
			os.system(cmd05)
		os.system(cmd1)
		os.system(cmd2)
