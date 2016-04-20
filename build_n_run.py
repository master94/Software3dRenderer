#!/usr/local/bin/python3

import os
import os.path
import subprocess
import sys

__build_dir = './build'

def exec_or_die(cmd):
    if subprocess.call(cmd, shell=True) != 0:
        exit(1)

if __name__ == '__main__':
    if not os.path.isdir(__build_dir):
        os.mkdir(__build_dir)

    project_dir = os.getcwd()
    os.chdir(__build_dir)

    exec_or_die('cmake {}'.format(project_dir))
    exec_or_die('make -j16')
    exec_or_die(' '.join(['./Software3dRenderer'] + sys.argv[1:]))
