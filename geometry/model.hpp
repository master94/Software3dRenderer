#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include "face.hpp"

struct Model
{
    std::vector<Face> faces;

    Model()
    {
    }

    Model(const std::vector<Face> &faces)
        : faces(faces)
    {
    }
};

#endif //MODEL_HPP
