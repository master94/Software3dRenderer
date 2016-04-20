#ifndef IMODELLOADER_HPP
#define IMODELLOADER_HPP

#include <iostream>
#include <geometry/model.hpp>

class IModelLoader
{
public:
    virtual ~IModelLoader() {}
    virtual void load(std::istream &stream) = 0;
    virtual bool isValid() const = 0;
    virtual Model model() const = 0;
};

#endif //IMODELLOADER_HPP
