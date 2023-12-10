#pragma once

#include "BaseModel.h"

class ArrayModel : public BaseModel {
private:
    size_t _vertexCount;

public:
    explicit ArrayModel(const std::vector<ModelAttribute>& vertexAttributes);

    virtual ~ArrayModel() = default;

protected:
    void drawCallback(const Shader& shader) const override;
};
