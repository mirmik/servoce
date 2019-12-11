#!/usr/bin/env python3
# coding: utf-8

import licant
from licant.cxx_modules import shared_library
from licant.modules import module, submodule

import licant.libs
import os


def get_occt_include_directory():
    dirs = ["/usr/include/", "/usr/local/include/"]
    subdirs = ["occt", "opencascade"]

    for d in dirs:
        if os.path.exists(d):
            for f in subdirs:
                fp = os.path.join(d, f)
                if os.path.exists(fp):
                    print("OpenCascade Headers directory:", fp)
                    return fp 

    raise Exception("can't find occt")

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

class Found(Exception):
    pass

add_sources = []
add_modules = []
add_moc = []

if os.name == "posix":
    try:
        for root, dirs, files in os.walk("/usr/include"):
           for dr in dirs:
               if dr == "qt5":
                   libqt_include_path = os.path.join(root, dr)
                   raise Found()
        else:
            print("NeedInstall Qt5")
            exit(-1)
    except (Found):
        pass


#    liboce_include_path = "/usr/local/include/opencascade/"
    liboce_include_path = get_occt_include_directory()
    lib_prefix = ""

elif os.name == "nt":
    liboce_include_path = "../../OpenCASCADE-7.3.0-vc14-64/opencascade-7.3.0/inc"
    lib_prefix = "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\"

module(
    "liboce",
    libs=[
        lib_prefix + "TKernel",
        lib_prefix + "TKMath",
        lib_prefix + "TKG2d",
        lib_prefix + "TKG3d",
        lib_prefix + "TKBRep",
        lib_prefix + "TKGeomBase",
        lib_prefix + "TKGeomAlgo",
        lib_prefix + "TKTopAlgo",
        lib_prefix + "TKPrim",
        lib_prefix + "TKBO",
        lib_prefix + "TKBool",
        lib_prefix + "TKOffset",
        lib_prefix + "TKService",
        lib_prefix + "TKV3d",
        lib_prefix + "TKOpenGl",
        lib_prefix + "TKFillet",
        lib_prefix + "TKSTL",
        lib_prefix + "TKBin",
        lib_prefix + "TKShHealing",
        lib_prefix + "TKMesh",
        lib_prefix + "TKHLR",
    ],
    include_paths=[liboce_include_path],
)

module(
    "libqt",
    libs=["Qt5Core", "Qt5Widgets", "Qt5Test", "Qt5Gui", "Qt5OpenGL"],
    include_paths=[libqt_include_path],
)

module(
    "servoce_sources",
    srcdir="src",
    sources=[
        "topo.cpp",
        "trans.cpp",
        "solid.cpp",
        "surface.cpp",
        "curve2.cpp",
        "curve3.cpp",
        "face.cpp",
        "wire.cpp",
        "boolops.cpp",
        "convert.cpp",
        "geombase.cpp",
        "geomprops.cpp",
        "view.cpp",
        "shape_view.cpp",
        "scene.cpp",
        "viewer.cpp",
        "camera.cpp",
        "prs3d.cpp",
        "interactive_object.cpp"
    ] + add_sources,
    moc=[] + add_moc,
    include_paths=["include", ".", "src"],
    mdepends=[
        "liboce",
        "nos",
    ] + add_modules,
    cxx_flags="-Wall -fPIC -DQT_NO_VERSION_TAGGING -ffunction-sections -fdata-sections",
    cc_flags="-Wall -fPIC -ffunction-sections -fdata-sections",
    ld_flags="-ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--as-needed",
)
