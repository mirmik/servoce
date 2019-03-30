from pyservoce.geom import Shape
import pyservoce.libservoce

def union(arr): 
	return Shape(pyservoce.libservoce.union([s.native() for s in arr]))

def difference(arr): 
	return Shape(pyservoce.libservoce.difference([s.native() for s in arr]))

def intersect(arr): 
	return Shape(pyservoce.libservoce.intersect([s.native() for s in arr]))