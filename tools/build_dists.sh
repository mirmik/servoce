./tools/collect_libs.py

python3.9 ./setup.py bdist_wheel
python3.8 ./setup.py bdist_wheel
python3.7 ./setup.py bdist_wheel
python3.6 ./setup.py bdist_wheel
#python3.5 ./setup.py bdist_wheel

#python2.7 ./setup.py bdist_wheel