#!/usr/bin/env python3

import pyservoce

#from PyQt5.QtWidgets import *
#from PyQt5.QtCore import *
#from PyQt5.QtGui import *

import sys

model = pyservoce.box(10,20,30)

svg = pyservoce.libservoce.getSVG(model.native())

print(svg)

#app = QApplication(sys.argv[1:])
#
#scn = pyservoce.Scene()
#scn.add(model)
#
#wdg = pyservoce.DisplayWidget(scn)
#wdg.show()
#
#app.exec()
#