#ifndef RECT_HPP
#define RECT_HPP

#include "point.hpp"

template <class T>
struct Rect_
{
    T top;
    T left;
    T width;
    T height;

    Rect_()
        : top(0)
        , left(0)
        , width(0)
        , height(0)
    {
    }

    Rect_(T top, T left, T width, T height)
        : top(top)
        , left(left)
        , width(width)
        , height(height)
    {
    }

    Rect_(const Point_<T> &tl, const Point_<T> &br)
        : top(tl.y)
        , left(tl.x)
        , width(br.x - tl.x)
        , height(br.y - tl.y)
    {
    }
};

using Rect = Rect_<int>;

#endif // RECT_HPP
