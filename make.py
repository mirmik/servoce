#!/usr/bin/env python3
# coding: utf-8

import licant
from licant.cxx_modules import shared_library
from licant.modules import module

import licant.libs
import os

licant.execute("servoce_inc.py")
licant.include("igris", "igris/igris.g.py")
licant.include("nos", "nos/nos.g.py")

install_lib_dir = "/usr/lib/"
install_inc_dir = "/usr/local/include/"

shared_library("cxxbuild/libservoce.so", 
    builddir="cxxbuild", 
    mdepends=["servoce_sources", "nos"],
    include_paths=["/usr/include/python3.6m"]
)


@licant.routine(deps=["cxxbuild/libservoce.so"])
def install():
    os.system("cp cxxbuild/libservoce.so {}".format(install_lib_dir + "libservoce.so"))
    os.system("cp -r include/servoce {}".format(install_inc_dir))
    print("success install")


licant.ex(default="cxxbuild/libservoce.so", colorwrap=True)
