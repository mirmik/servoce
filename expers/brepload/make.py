#!/usr/bin/env python3
# coding: utf-8

import licant
import licant.libs
from licant.cxx_modules import application

full_list = [
    "TKBinL",
    "TKBin",
    "TKBinTObj",
    "TKBinXCAF",
    "TKBool",
    "TKBO",
    "TKBRep",
    "TKCAF ",
    "TKCDF ",
    "TKDCAF",
    "TKDraw",
    "TKernel",
    "TKFeat",
    "TKFillet",
    "TKG2d",
    "TKG3d",
    "TKGeomAlgo",
    "TKGeomBase",
    "TKHLR",
    "TKIGES",
    "TKLCAF",
    "TKMath",
    "TKMesh",
    "TKMeshVS",
    "TKOffset",
    "TKOpenGl",
    "TKPrim",
    "TKQADraw",
    "TKService",
    "TKShHealing ",
    "TKStdL",
    "TKStd ",
    "TKSTEP209 ",
    "TKSTEPAttr",
    "TKSTEPBase",
    "TKSTEP",
    "TKSTL",
    "TKTObjDRAW",
    "TKTObj",
    "TKTopAlgo",
    "TKTopTest",
    "TKV3d",
    "TKVCAF",
    "TKViewerTest",
    "TKVRML",
    "TKXCAF",
    "TKXCAF",
    "TKXDEDRAW",
    "TKXDEIGES",
    "TKXDESTEP",
    "TKXMesh",
    "TKXmlL",
    "TKXml",
    "TKXmlTObj",
    "TKXmlXCAF",
    "TKXSBase",
    "TKXSDRAW",
]

application(
    "target",
    include_paths=["/usr/local/include/opencascade/"],
    sources=["main.cpp"],
    libs=["servoce", "igris", "nos", *full_list]
)

licant.ex(default="target")
