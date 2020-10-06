#!/usr/bin/env python3

import os
import shutil

for d in [f.path for f in os.scandir(".") if f.is_dir()]:
	shutil.rmtree(d)
