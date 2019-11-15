This library is part of zencad project.
Servoce wraps opencascade core for integrate with zencad.

Status:  
![](https://travis-ci.com/mirmik/servoce.svg?branch=master) - master  
![](https://travis-ci.com/mirmik/servoce.svg?branch=dev) - dev  

[ZenCad](https://github.com/mirmik/zencad)

Install from PyPi.
------------------
```
python3 -m pip install pyservoce
```

Install from Source Code.
-------------------------------------
1. Get Dependies. (OCCT, PyBind11, Licant) 
```sh
sudo add-apt-repository ppa:freecad-maintainers/occt-releases -y
sudo add-apt-repository ppa:freecad-maintainers/freecad-stable -y
sudo apt-get update
sudo apt install -y libocct-foundation-7.3 libocct-ocaf-7.3 libocct-data-exchange-7.3 libocct-foundation-dev libocct-ocaf-dev libocct-data-exchange-dev
sudo apt install -y python3-pybind11
python3 -m pip install licant --user
```

2. Get source code
```sh
git clone https://github.com/mirmik/servoce --recursive
cd servoce
```

3. Install as python package from sources.
```sh
python3 ./setup.py install --user
```

4. Install as dynamic library with CMake.
```sh
source ./tools/set_occt_paths.sh
cmake .
cmake --build
cmake --build . --target install
```

5. Install as dynamic library with Licant.
```sh
./make.py
sudo ./make.py install
```

Depend repositories:
--------------------
[https://github.com/mirmik/igris](https://github.com/mirmik/igris)  
[https://github.com/mirmik/nos](https://github.com/mirmik/nos)  
[https://github.com/mirmik/licant](https://github.com/mirmik/licant)  