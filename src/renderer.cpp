#include "renderer.hpp"

#include <cmath>
#include <iostream>
#include <limits>

#include <geometry/point.hpp>
#include <geometry/rect.hpp>
#include <geometry/vec.hpp>
#include <geometry/triangle.hpp>
#include <geometry/utils.hpp>
#include <ICanvas.hpp>

namespace
{
    const Vec3_<float> &gDefaultLightDirection()
    {
        static const Vec3_<float> gLightDir(0, 0, 1);
        return gLightDir;
    }

    void processVertices(Vertex *vertices, int width, int height)
    {
        const int hw = width / 2;
        const int hh = height / 2;

        for (int i = 0; i < 3; ++i) {
            vertices[i].x = hw * (1 + vertices[i].x);
            vertices[i].y = hh * (1 + vertices[i].y);
        }
    }

    float interpolate(float v1, float v2, float v3, const Vec3_<float> &barCoords)
    {
        return barCoords.x * v1 + barCoords.y * v2 + barCoords.z * v3;
    }

    int getColor(const TGAImage &texture, float x, float y)
    {
        const TGAColor color= texture.get(x * texture.get_width(), y * texture.get_height());
        return QColor(color[2], color[1], color[0]).rgb();
    }
}

Renderer::Renderer(ICanvas &canvas)
    : mCanvas(canvas)
    , mZBuffer(canvas.size().width() * canvas.size().height(), std::numeric_limits<float>::lowest())
    , mLightDirection(gDefaultLightDirection())
{
}

Renderer::~Renderer()
{
}

Vertex Renderer::lightPosition() const
{
    return mLightPosition;
}

void Renderer::setLightPosition(const Vertex &pos)
{
    mLightPosition = pos;
}

Vec3_<float> Renderer::lightDirection() const
{
    return mLightDirection;
}

void Renderer::setLightDirection(const Vec3_<float> &dir)
{
    mLightDirection = dir;
}

void Renderer::renderModel(const Model &model, const TGAImage &texture)
{
    for (const auto &face : model.faces) {
        fillFace(face, texture);
    }
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, int color)
{
    const bool highSlope = abs(y2 - y1) > abs(x2 - x1);
    if (highSlope) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x2 < x1) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int currY = y1;
    int errY = 0;
    for (int x = x1; x <= x2; ++x) {
        if (highSlope)
            mCanvas.setPixelColor(currY, x, color);
        else
            mCanvas.setPixelColor(x, currY, color);

        errY += 2 * abs(dy);

        if (errY > dx) {
            currY += (dy > 0 ? +1 : -1);
            errY -= 2 * dx;
        }
    }
}

void Renderer::drawLine(const Point &p1, const Point &p2, int color)
{
    drawLine(p1.x, p1.y, p2.x, p2.y, color);
}

void Renderer::fillFace(const Face &face1, const TGAImage &texture)
{
    Face face = face1;
    Vertex *v = face.points;
    Vertex *tv = face.texture;

    const auto n = normal(v[0], v[1], v[2]);
    const float lum = fabs(n.angleCos(mLightDirection));

    if (1 || lum > 0) {
        processVertices(v, mCanvas.size().width(), mCanvas.size().height());

        const Point p1(v[0].x, v[0].y);
        const Point p2(v[1].x, v[1].y);
        const Point p3(v[2].x, v[2].y);

        const auto brect = boundingRect<std::vector, int>({ p1, p2, p3 });

        const Triangle tr(p1, p2, p3);

        for (int i = 0; i < brect.height; ++i) {
            for (int j = 0; j < brect.width; ++j) {
                const Point p(brect.left + j, brect.top + i);
                const auto barCoords = barycentric(tr, Point(brect.left + j, brect.top + i));

                if (barCoords.x >= 0 && barCoords.y >= 0 && barCoords.z >= 0) {
                    const float z = barCoords.x * v[0].z + barCoords.y * v[1].z + barCoords.z * v[2].z;

                    if (z > mZBuffer[p.y * mCanvas.size().width() + p.x]) {
                        mZBuffer[p.y * mCanvas.size().width() + p.x] = z;
                        const int color = getColor(texture, interpolate(tv[0].x, tv[1].x, tv[2].x, barCoords), interpolate(tv[0].y, tv[1].y, tv[2].y, barCoords));
                        mCanvas.setPixelColor(brect.left + j, brect.top + i, color);
                    }
                }
            }
        }
    }
}
