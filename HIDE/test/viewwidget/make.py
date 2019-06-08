#!/usr/bin/env python3
# coding: utf-8

import licant
import licant.libs
from licant.cxx_modules import application

licant.libs.include("servoce")

application(
    "target",
    sources=["main.cpp"],
    # libs = ["servoce"],
    include_modules=["servoce_sources"],
)

licant.ex(default="target")
