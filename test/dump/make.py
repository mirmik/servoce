#!/usr/bin/env python3
#coding: utf-8

import licant
from licant.cxx_modules import application

application("target", 
	sources = [
		"main.cpp"
	],
	libs = ["servoce"],
)

licant.ex(default = "target")