#ifndef RENDERER_HPP
#define RENDERER_HPP

class ICanvas;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void drawLine(int x1, int y1, int x2, int y2, int color, ICanvas &canvas);
};

#endif //RENDERER_HPP

