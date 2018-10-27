#!/usr/bin/env python3
#coding: utf-8

import licant
import licant.libs
from licant.cxx_modules import application

licant.libs.include("servoce")

application("target", 
	sources = [
		"main.cpp"
	],
	include_modules = ["servoce_sources"],

	cxx_flags = "--pedantic-error -Wall"
)

licant.ex(default = "target")