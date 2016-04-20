Simple software 3D renderer

Created for educational purposes to figure out how that rendering magic really works.

Features implemented:
* Bresenham's line rastering algo
* Obj model loading
* Model wireframe rendering
* ... to be continued

Build prerequisites:
* C++11 compatible compiler
* Qt5.4 (QtWidgets for simple point-by-point drawing)
* CMake 2.8+
* Python3

Build & Run:
./build_n_run.py ./test/data/african_head.obj

Based on cool crash-course by Dmitry V. Sokolov
https://github.com/ssloy/tinyrenderer/wiki
