#!/usr/bin/env python3
# coding: utf-8

import licant
from licant.cxx_modules import shared_library
from licant.modules import module, submodule

import licant.libs
import os

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

# licant.include("nos", local_tunel="build/nos")


#class Found(Exception):
#    pass
#
#
#try:
#    for root, dirs, files in os.walk("/usr/include"):
#        for dr in dirs:
#            if dr == "qt5":
#                libqt_include_path = os.path.join(root, dr)
#                raise Found()
#    else:
#        print("NeedInstall Qt5")
#        exit(-1)
#except (Found):
#    pass

# liboce_include_path = "/usr/include/oce/"
liboce_include_path = "../../OpenCASCADE-7.3.0-vc14-64/opencascade-7.3.0/inc"
#python_include_prefix = "/usr/include/"

module(
    "liboce",
    libs=[
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKernel",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKMath",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKG2d",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKG3d",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKBRep",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKGeomBase",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKGeomAlgo",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKTopAlgo",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKPrim",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKBO",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKBool",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKOffset",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKService",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKV3d",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKOpenGl",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKFillet",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKSTL",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKBin",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKShHealing",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKMesh",
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKHLR",
    ],
    include_paths=[liboce_include_path],
)

module(
    "libqt",
    libs=["Qt5Core", "Qt5Widgets", "Qt5Test", "Qt5Gui", "Qt5OpenGL"],
    #include_paths=[libqt_include_path],
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
        "face.cpp",
        "wire.cpp",
        "boolops.cpp",
        "display.cpp",
        # "test.cpp",
        "convert.cpp",
        "geombase.cpp",
        "view.cpp",
        "shape_view.cpp",
        "scene.cpp",
        "viewer.cpp",
        "camera.cpp",
#        "display/mainwidget.cpp",
#        "display/dispwidget.cpp",
#        "display/dispwidget_qt.cpp",
#        "display/icons.cpp",
        # 		"occversion.cpp",
        # "widgets/gtk_widget.cpp"
    ],
   # moc=["local/display.h"],
    include_paths=["include", ".", "src"],
    mdepends=[
        "liboce",
      #  "libqt",
        # 		submodule("gxx.include"),
        # 		submodule("gxx", "posix"),
        # 		submodule("gxx.print", "cout"),
        # 		submodule("gxx.dprint", "cout"),
        "nos",
    ],
    cxx_flags="-Wall -fPIC -DQT_NO_VERSION_TAGGING -ffunction-sections -fdata-sections",
    cc_flags="-Wall -fPIC -ffunction-sections -fdata-sections",
    ld_flags="-ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--as-needed",
)
