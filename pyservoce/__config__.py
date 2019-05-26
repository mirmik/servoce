import sys

extra_dll_dir = os.path.join(os.path.dirname(__file__), "..")

print(sys.platform)

if (sys.platform == 'win32' or sys.platform == 'win64') and os.path.isdir(extra_dll_dir):
    os.environ.setdefault('PATH', '')
    os.environ['PATH'] += os.pathsep + extra_dll_dir