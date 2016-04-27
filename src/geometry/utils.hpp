#ifndef UTILS_HPP
#define UTILS_HPP

#include <limits>

#include "point.hpp"
#include "vec.hpp"
#include "triangle.hpp"
#include "rect.hpp"
#include "vertex.hpp"

template <template <typename...> class Container, class T>
inline
Rect boundingRect(const Container<Point_<T>> &container)
{
   T top    = std::numeric_limits<T>::max();
   T left   = std::numeric_limits<T>::max();
   T bottom = std::numeric_limits<T>::min();
   T right  = std::numeric_limits<T>::min();

   for (const auto &point : container) {
       top    = std::min(top   , point.y);
       left   = std::min(left  , point.x);
       bottom = std::max(bottom, point.y);
       right  = std::max(right , point.x);
   }

   return Rect_<T>(top, left, right - left, bottom - top);
}

template <class T>
Vec2_<T> operator-(const Point_<T> &p1, const Point_<T> &p2)
{
   return Vec2_<T>(p2.x - p1.x, p2.y - p1.y);
}

template <class T>
inline
Vec3_<float> barycentric(const Triangle_<T> &tr, const Point_<T> &point)
{
   const Vec2_<T> ab = tr.p1 - tr.p2;
   const Vec2_<T> ac = tr.p1 - tr.p3;
   const Vec2_<T> pa = point - tr.p1;
   const auto coord = Vec3_<T>(ab.x, ac.x, pa.x).cross(Vec3_<T>(ab.y, ac.y, pa.y));
   return Vec3_<float>(1.0f - (coord.x + coord.y) / float(coord.z), coord.y / float(coord.z), coord.x / float(coord.z));
}

template <class T>
inline
bool isPointInsideTriangle(const Point_<T> &point, const Triangle_<T> &triangle)
{
   const auto barycentricCoords = barycentric(triangle, point);
   return barycentricCoords.x >= 0 && barycentricCoords.y >= 0 && barycentricCoords.z >= 0;
}

inline
Vec3_<float> normal(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    const auto ab = Vec3_<float>(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
    const auto ac = Vec3_<float>(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
    return ab.cross(ac).normalize();
}

#endif // UTILS_HPP
