#!/usr/bin/env python3

from wheel.bdist_wheel import bdist_wheel as bdist_wheel_
from setuptools import setup, Extension, Command
from distutils.util import get_platform
import os
import licant

licant.include("nos", "nos/nos.g.py")
licant.include("igris", "igris/igris.g.py")
licant.cxx_objects("nos-objects", mdepends=["nos", "igris.include"])
nosopts = licant.core.core.get("nos-objects").finalopts

ext_include_paths = ["C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\inc"] + nosopts["include_paths"]

class bdist_wheel(bdist_wheel_):
    def finalize_options(self):
        from sys import platform as _platform

        platform_name = get_platform()

        if _platform == "linux" or _platform == "linux2":
            # Linux
            if platform_name == "linux-i686":
                platform_name = "manylinux1_i686"
            else:
                platform_name = "manylinux1_x86_64"

        bdist_wheel_.finalize_options(self)
        self.universal = True
        self.plat_name_supplied = True
        self.plat_name = platform_name


liboce_include_path = "/usr/local/include/opencascade"
pyservoce_lib = Extension(
    "pyservoce.libservoce",
    sources= nosopts["sources"] + [
        "src/pywrap.cpp",
        "src/surface.cpp",
        "src/curve2.cpp",
        "src/b64.cpp",
        "src/topo.cpp",
        "src/trans.cpp",
        "src/solid.cpp",
        "src/face.cpp",
        "src/wire.cpp",
        "src/boolops.cpp",
        "src/geombase.cpp",
        "src/convert.cpp",
        "src/view.cpp",
        "src/scene.cpp",
        "src/viewer.cpp",
        "src/shape_view.cpp",
        "src/camera.cpp",
    ],
    extra_compile_args=["-fPIC", "-std=c++14", "-DNOTRACE=1"],
    extra_link_args=["-Wl,-rpath,$ORIGIN/libs"],
    include_dirs=[liboce_include_path, "src", "include"] + ext_include_paths,
    #library_dir=["C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib"],
    libraries=[
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
)

pyservoce_lib2 = Extension(
    "pyservoce.libservoce",
    sources= ["src/test.cpp"],
    libraries=[
        "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\TKernel",
    ],
)

setup(
    name="pyservoce",
    packages=["pyservoce"],
    version="1.9.5",
    license="MIT",
    description="CAD system for righteous zen programmers ",
    author="mirmik",
    author_email="mirmikns@yandex.ru",
    url="https://github.com/mirmik/servoce",
    long_description=open("README.md", "r").read(),
    long_description_content_type="text/markdown",
    keywords=["testing", "cad"],
    classifiers=[],
    package_data={"pyservoce": "libs\\*"},
    include_package_data=True,
    ext_modules=[pyservoce_lib2],
    cmdclass={"bdist_wheel": bdist_wheel},
)
