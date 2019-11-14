This library is part of zencad project.
Servoce wraps opencascade core for integrate with zencad.

![](https://travis-ci.com/mirmik/servoce.svg?branch=master)  
[ZenCad](https://github.com/mirmik/zencad)

Install from PyPi.
------------------
```
python3 -m pip install pyservoce
```

Install from Source Code.
-------------------------------------
1. Get Dependies. (OCCT, PyBind11, Licant) 
```
sudo add-apt-repository ppa:freecad-maintainers/occt-releases -y
sudo add-apt-repository ppa:freecad-maintainers/freecad-stable -y
sudo apt-get update
sudo apt install -y libocct-foundation-7.3 libocct-ocaf-7.3 libocct-data-exchange-7.3 libocct-foundation-dev libocct-ocaf-dev libocct-data-exchange-dev
sudo apt install -y python3-pybind11
python3 -m pip install licant --user
```

2. Build and Install
```
git clone https://github.com/mirmik/servoce --recursive
cd servoce
python3 ./setup.py install --user
```

Depend repositories:
--------------------
[https://github.com/mirmik/igris](https://github.com/mirmik/igris)  
[https://github.com/mirmik/nos](https://github.com/mirmik/nos)  
[https://github.com/mirmik/licant](https://github.com/mirmik/licant)  