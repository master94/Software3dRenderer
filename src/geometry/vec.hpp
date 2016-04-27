#ifndef VEC_HPP
#define VEC_HPP

template <class T>
struct Vec2_
{
    T x;
    T y;

    Vec2_(T x, T y)
        : x(x)
        , y(y)
    {
    }
};

template <class T>
struct Vec3_
{
    T x;
    T y;
    T z;

    Vec3_(T x, T y, T z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    Vec3_<T> cross(const Vec3_<T> &v) const
    {
        return Vec3_<T>(
                y * v.z - z * v.y,
                v.x * z - x * v.z,
                x * v.y - y * v.x);
    }

    T dot(const Vec3_<T> &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3_<T> &normalize()
    {
        const float len = pow(pow(x, 2) + pow(y, 2) + pow(z, 2), 0.5);
        x /= len;
        y /= len;
        z /= len;
        return *this;
    }
};

#endif // VEC_HPP
