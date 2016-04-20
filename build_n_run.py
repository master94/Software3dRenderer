#!/usr/local/bin/python3

import os
import os.path
import subprocess
import sys

__build_dir = './build'
__project_dir = './src'
__exe_name = 'Software3dRenderer'

def exec_or_die(cmd):
    if subprocess.call(cmd, shell=True) != 0:
        exit(1)

if __name__ == '__main__':
    if not os.path.isdir(__build_dir):
        os.mkdir(__build_dir)

    work_dir = os.getcwd()
    project_dir = os.path.join(work_dir, __project_dir)
    os.chdir(__build_dir)

    exec_or_die('cmake {}'.format(project_dir))
    exec_or_die('make -j16')

    os.chdir(work_dir)
    bin_path = os.path.join(__build_dir, __exe_name)
    exec_or_die(' '.join([bin_path] + sys.argv[1:]))
