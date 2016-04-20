#ifndef OBJ_MODEL_LOADER_H
#define OBJ_MODEL_LOADER_H

#include <vector>
#include <iostream>
#include <regex>

#include <geometry/model.hpp>
#include "IModelLoader.hpp"

class ObjModelLoader : public IModelLoader
{
public:
    ObjModelLoader();
    ~ObjModelLoader();
    void load(std::istream &stream) override;
    bool isValid() const override;
    Model model() const override;

private:
    struct LineParser
    {
        std::regex regexp;
        std::function<void(const std::string &)> parserFunc;

        LineParser(const std::regex &regexp,
                   const std::function<void(const std::string &)> &parserFunc)
            : regexp(regexp)
            , parserFunc(parserFunc)
        {
        }
    };

private:
    void buildLineParsers();
    bool parseLine(std::istream &stream);

    void parseVertexLine(const std::string &line);
    void parseTextureLine(const std::string &line);
    void parseNormalLine(const std::string &line);
    void parseFaceLine(const std::string &line);

private:
    std::vector<LineParser> mLineParsers;
    std::vector<Vertex> mVertices;
    std::vector<Vertex> mTextures;
    std::vector<Vertex> mNormals;
    std::vector<Face> mFaces;

};

#endif //OBJ_MODEL_LOADER_H
