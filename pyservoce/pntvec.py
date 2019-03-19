import pyservoce.libservoce
import pyservoce.trans

class xy:
	def get_x(self):
		return self.arr[0]

	def get_y(self):
		return self.arr[1]

	def set_x(self, x): 
		self.arr[0] = x 

	def set_y(self, y): 
		self.arr[1] = y

	def __iter__(self):
		return iter(self.arr)

	def __getitem__(self, key):
		return self.arr[key]

	def __setitem__(self, key, value):
		self.arr[key] = value

	x = property(get_x, set_x)
	y = property(get_y, set_y)

class xyz(xy):
	def get_z(self):
		return self.arr[2]
	
	def set_z(self, z): 
		self.arr[2] = z

	z = property(get_z, set_z)

class point2(xy):
	def __init__(self, *args):
		if len(args) == 0:
			self.arr = (0, 0, 0)

		elif len(args) == 1:
			self.arr = (args[0][0], args[0][1], args[0][2])

		elif len(args) == 2:
			self.arr = (args[0], args[1], 0)

		else:
			raise Exception("point2: Too many arguments: {}".format(args))

	def native(self): return pyservoce.libservoce.point2_native(self.x, self.y)
	def __repr__(self): return "point2({},{})".format(self.arr[0], self.arr[1])
	def __getstate__(self): return self.arr
	def __setstate__(self, obj): self.arr=obj 

class point3(xyz, pyservoce.trans.Transformable):
	def __init__(self, *args):
		if len(args) == 0:
			self.arr = (0, 0, 0)

		elif len(args) == 1:
			self.arr = (args[0][0], args[0][1], args[0][2])

		elif len(args) == 2:
			self.arr = (args[0], args[1], 0)

		elif len(args) == 3:
			self.arr = (args[0], args[1], args[2])
		
		else:
			raise Exception("point3: Too many arguments: {}".format(args))

	def native(self): return pyservoce.libservoce.point3_native(self.arr[0], self.arr[1], self.arr[2])
	def __repr__(self): return "point3({},{},{})".format(self.arr[0], self.arr[1], self.arr[2])
	def __getstate__(self): return self.arr
	def __setstate__(self, obj): self.arr=obj 

class vector3(xyz, pyservoce.trans.Transformable):
	def __init__(self, *args):
		if len(args) == 0:
			self.arr = (0, 0, 0)

		elif len(args) == 1:
			self.arr = (args[0][0], args[0][1], args[0][2])

		elif len(args) == 2:
			self.arr = (args[0], args[1], 0)

		elif len(args) == 3:
			self.arr = (args[0], args[1], args[2])
		
		else:
			raise Exception("vector3: Too many arguments: {}".format(args))

	def native(self): return pyservoce.libservoce.vector3_native(self.arr[0], self.arr[1], self.arr[2])
	def __repr__(self): return "vector3({},{},{})".format(self.arr[0], self.arr[1], self.arr[2])
	def __getstate__(self): return self.arr
	def __setstate__(self, obj): self.arr=obj 