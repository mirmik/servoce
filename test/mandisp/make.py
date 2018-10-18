#!/usr/bin/env python3
#coding: utf-8

import licant
import licant.libs
from licant.cxx_modules import application

licant.libs.include("servoce")

import os

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

application("target", 
	sources = [
		"main.cpp"
	],
	moc = [
		"main.h"
	],
	include_paths = [libqt_include_path, "."],
	include_modules = ["servoce_sources"]
)

licant.ex(default = "target")