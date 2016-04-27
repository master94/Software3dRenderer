#ifndef POINT_HPP
#define POINT_HPP

template <class T>
struct Point_
{
    T x;
    T y;

    Point_()
        : x(0)
        , y(0)
    {
    }

    Point_(T x, T y)
        : x(x)
        , y(y)
    {
    }
};

using Point = Point_<int>;

#endif // POINT_HPP
