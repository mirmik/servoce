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

add_sources = []
add_modules = []
add_moc = []

if os.name == "posix":
    liboce_include_path = "/usr/local/include/opencascade/"
    lib_prefix = ""

elif os.name == "nt":
    liboce_include_path = "../../OpenCASCADE-7.3.0-vc14-64/opencascade-7.3.0/inc"
    lib_prefix = "C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib\\"

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

pyservoce_lib = Extension(
    "pyservoce.libservoce",
    sources= [
        "src/pywrap.cpp",
        "src/geombase_py.cpp",
        "src/color_py.cpp",
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
        "src/prs3d.cpp",
        "src/interactive_object.cpp",
    ] + nosopts["sources"],
    extra_compile_args=["-fPIC", "-std=c++14", "-DNODTRACE=1", "-DNOTRACE=1"],
    extra_link_args=["-Wl,-rpath,$ORIGIN/libs"],
    include_dirs=[liboce_include_path, "src", "include"] + nosopts["include_paths"],
    #library_dir=["C:\\OpenCASCADE-7.3.0-vc14-64\\opencascade-7.3.0\\win64\\vc14\\lib"],
    libraries=[
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
    package_data={"pyservoce": ["libs\\*"]},
    include_package_data=True,
    ext_modules=[pyservoce_lib],
    cmdclass={"bdist_wheel": bdist_wheel},
)
