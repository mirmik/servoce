#!/usr/bin/python3
#coding:utf-8

import os

os.system("mkdir -p pyservoce/libs")

listlibs = [
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
]

filelist = os.listdir("/usr/local/lib/")

for l in listlibs:
	for f in filelist:
		if l + '.so.7.3.0' in f:
			cmd0 = "cp {0} pyservoce/libs/".format(os.path.join("/usr/local/lib/",f))
			cmd05= "patchelf --set-rpath '$ORIGIN' pyservoce/libs/{0}".format(f)
			cmd1 = "ln -s {2}/pyservoce/libs/{0} {2}/pyservoce/libs/{1}".format(f, f[:-4], os.getcwd())
			cmd2 = "ln -s {2}/pyservoce/libs/{0} {2}/pyservoce/libs/{1}".format(f, f[:-6], os.getcwd())
			
			print(cmd0)
			print(cmd05)
			print(cmd1)
			print(cmd2)
			
			os.system(cmd0)
			os.system(cmd05)
			os.system(cmd1)
			os.system(cmd2)