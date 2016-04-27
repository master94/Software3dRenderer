#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

template <class T>
struct Triangle_
{
    Point_<T> p1;
    Point_<T> p2;
    Point_<T> p3;

    Triangle_(const Point_<T> &p1, const Point_<T> &p2, const Point_<T> &p3)
        : p1(p1)
        , p2(p2)
        , p3(p3)
    {
    }
};

using Triangle = Triangle_<int>;

#endif // TRIANGLE_HPP
