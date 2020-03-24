#!/usr/bin/env python3

import licant

licant.include("servoce")
qt_inc = licant.attribute("qt_inc") 
occt_inc = licant.attribute("occt_inc") 

licant.cxx_application("target",
	sources=["main.cpp"],
	mdepends=["servoce_sources", "servoce_display", "libqt"],
	libs=["X11", "gl2ps", "nos", "igris", "glut", "GL"],
	include_paths = [qt_inc, occt_inc]
)

licant.ex("target")