#!/usr/bin/env python3
# coding: utf-8

import licant
import licant.libs
from licant.cxx_modules import application

licant.libs.include("servoce")
licant.libs.include("nos")

application(
    "target",
    sources=["main.cpp"],
    # libs = ["servoce"],
    mdepends=["servoce_sources", "nos"],
    cxx_flags="--pedantic-error -Wall",
)

licant.ex(default="target")
