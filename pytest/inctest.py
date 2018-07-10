#!/usr/bin/python3
#coding: utf-8

import pyservoce

m = pyservoce.make_box(8,9,10)

scn = pyservoce.Scene()

scn.add(m, pyservoce.Color(0.3,0.3,0.3))

pyservoce.display_scene(scn)