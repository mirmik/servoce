#!/usr/bin/env python3
# coding: utf-8

import licant
import licant.libs
from licant.cxx_modules import application

licant.include("nos", "../../../nos/nos.g.py")
licant.execute("../../../servoce_inc.py")

application(
    "target",
    sources=["main.cpp"],
    include_paths=["."],
    mdepends=["servoce_sources", "nos"],
)

licant.ex(default="target")
