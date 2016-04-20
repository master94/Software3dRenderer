#ifndef VERTEX_HPP
#define VERTEX_HPP

struct Vertex
{
    float x;
    float y;
    float z;

    Vertex()
        : x(0)
        , y(0)
        , z(0)
    {
    }

    Vertex(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }
};

#endif //VERTEX_HPP
