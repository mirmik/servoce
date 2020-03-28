#!/usr/bin/env python3
# coding: utf-8

import pyservoce

print("make box")
pyservoce.box(1,1,1)

#print("make Scene")
#try:
#	pyservoce.Scene()
#except Exception as ex:
#	print("non fatal: {}", ex)