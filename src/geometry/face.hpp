#ifndef FACE_HPP
#define FACE_HPP

#include "vertex.hpp"

struct Face
{
    Vertex points[3];
    Vertex normals[3];
    Vertex texture[3];
};

#endif //FACE_HPP
