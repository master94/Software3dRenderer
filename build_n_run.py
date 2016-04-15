#!/usr/local/bin/python3

import os
import os.path
import subprocess

__build_dir = './build'

if not os.path.isdir(__build_dir):
    os.mkdir(__build_dir)

project_dir = os.getcwd()
os.chdir(__build_dir)
subprocess.call('cmake {}'.format(project_dir), shell=True)
subprocess.call('make -j16', shell=True)
subprocess.call('./Software3dRenderer')
