#pragma once

#include "BaseModel.h"

#include <vector>

class ElementModel : public BaseModel {
private:
    std::unique_ptr<Buffer> _ebo;

    size_t _elementCount;

public:
    ElementModel(
        const std::vector<GLushort>& elements,
        const std::vector<ModelAttribute>& vertexAttributes
    );

    virtual ~ElementModel() = default;

protected:
    void drawCallback(const Shader& shader) const override;
};
