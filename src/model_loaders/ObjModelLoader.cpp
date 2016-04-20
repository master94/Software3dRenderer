#include "ObjModelLoader.hpp"

#include <vector>

#include <geometry/vertex.hpp>
#include <geometry/face.hpp>
#include <utils.hpp>

ObjModelLoader::ObjModelLoader()
{
    buildLineParsers();
}

ObjModelLoader::~ObjModelLoader()
{
}

void ObjModelLoader::load(std::istream &stream)
{
    while (parseLine(stream));
}

bool ObjModelLoader::isValid() const
{
    return !mFaces.empty();
}

Model ObjModelLoader::model() const
{
   return Model(mFaces);
}

void ObjModelLoader::buildLineParsers()
{
    using namespace std::placeholders;

    mLineParsers.clear();
    mLineParsers.emplace_back(std::regex("^v .*$" ),
        std::bind(&ObjModelLoader::parseVertexLine , this, _1));
    mLineParsers.emplace_back(std::regex("^vt .*$"),
        std::bind(&ObjModelLoader::parseTextureLine, this, _1));
    mLineParsers.emplace_back(std::regex("^vn .*$"),
        std::bind(&ObjModelLoader::parseNormalLine , this, _1));
    mLineParsers.emplace_back(std::regex("^f .*$" ),
        std::bind(&ObjModelLoader::parseFaceLine   , this, _1));
}

bool ObjModelLoader::parseLine(std::istream &stream)
{
    std::string line;
    if (std::getline(stream, line)) {
        for (const auto &p : mLineParsers) {
            if (std::regex_match(line, p.regexp)) {
                p.parserFunc(line);
            }
        }
        return true;
    }

    return false;
}

void ObjModelLoader::parseVertexLine(const std::string &line)
{
    const auto parts = Utils::split(line, ' ', 1);
    const auto vertex = Utils::map<std::string, float>(parts);
    mVertices.emplace_back(vertex[0], vertex[1], vertex[2]);
}

void ObjModelLoader::parseTextureLine(const std::string &line)
{
    const auto parts = Utils::split(line, ' ', 1);
    const auto vertex = Utils::map<std::string, float>(parts);
    mTextures.emplace_back(vertex[0], vertex[1], vertex[2]);
}

void ObjModelLoader::parseNormalLine(const std::string &line)
{
    const auto parts = Utils::split(line, ' ', 1);
    const auto vertex = Utils::map<std::string, float>(parts);
    mNormals.emplace_back(vertex[0], vertex[1], vertex[2]);
}

void ObjModelLoader::parseFaceLine(const std::string &line)
{
    Face face;
    const auto parts = Utils::split(line, ' ', 1);

    for (size_t i = 0; i < parts.size(); ++i) {
        const auto indicesStr = Utils::split(parts[i], '/');
        const auto indices = Utils::map<std::string, size_t>(indicesStr);
        face.points [i] = mVertices[indices[0] - 1];
        face.normals[i] = mNormals [indices[1] - 1];
        face.texture[i] = mTextures[indices[2] - 1];
    }

    mFaces.push_back(face);
}
