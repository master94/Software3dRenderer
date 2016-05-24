#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <geometry/point.hpp>
#include <geometry/model.hpp>
#include <geometry/vec.hpp>
#include <3dparty/tgaimage.h>

class ICanvas;

class Renderer
{
public:
    Renderer(ICanvas &canvas);
    ~Renderer();

    Vertex lightPosition() const;
    void setLightPosition(const Vertex &pos);

    Vec3_<float> lightDirection() const;
    void setLightDirection(const Vec3_<float> &dir);

    void renderModel(const Model &model, const TGAImage &texture);

private:
    void drawLine(int x1, int y1, int x2, int y2, int color);
    void drawLine(const Point &p1, const Point &p2, int color);

    void fillFace(const Face &face, const TGAImage &texture);

private:
    ICanvas &mCanvas;
    Vertex mLightPosition;
    Vec3_<float> mLightDirection;
    std::vector<float> mZBuffer;

};

#endif //RENDERER_HPP

