#!/usr/bin/env python3
# coding:utf-8

import io
import os
import sys

#vers = "7.3.0"
vers = "7"

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

	#darwin
	"TKCAF",
	"TKLCAF",
	"TKCDF",
	"TKBinL",

]

def get_occt_library_directory():
	dirs = ["/usr/local/lib/", "/usr/lib/x86_64-linux-gnu/"]
	
	for d in dirs:
		if os.path.exists(d) and ("libTKernel.so" in os.listdir(d) or "libTKernel.dylib" in os.listdir(d)):
			return d 
	else:
		raise Exception("can't find occt")
occt_libs_dir = get_occt_library_directory()

filelist = os.listdir(occt_libs_dir)


def debian_collect(f):
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

def darwin_collect(f,l):
	import subprocess 

	def do_command(cmd):
		print(cmd)
		os.system(cmd)

	lib = f"pyservoce/libs/{f}"

	do_command(f"cp {occt_libs_dir}/{f} {lib}")

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

for l in listlibs:
	if sys.platform == "darwin":
		fl = "lib" + l + ".{}.dylib".format(vers)
	else:
		fl = "lib" + l + ".so.{}".format(vers)	

	print(fl)

	if fl in filelist:
		f = fl

		if sys.platform == "darwin":
			darwin_collect(f, l)

		else:
			debian_collect(f)



