#pragma once

#include "BaseModel.h"

#include <vector>

#include "../util/util.h"

class ElementModel : public BaseModel {
private:
    Buffer *_vbo;
    Buffer *_ebo;

    size_t _elementCount;

public:
    template<typename T>
    ElementModel(
            Shader *shader,
            Texture *texture,
            const std::vector<T> &vertices,
            const std::vector<GLushort> &elements
    ) :
            BaseModel(shader, texture),
            _elementCount(elements.size()) {

        _vao->use([this, &vertices, &elements]() {
            _vbo = Buffer::create(Buffer::Type::ARRAY);
            _vbo->setData(vertices);
            this->addAttributeBuffer(_vbo, 0, 3); //TODO: fixed components

            _ebo = Buffer::create(Buffer::Type::ELEMENT_ARRAY);
            _ebo->setData(elements);
            this->addBuffer(_ebo);
        });
    }

    template<typename T>
    ElementModel(
            Shader *shader,
            const std::vector<T> &vertices,
            const std::vector<GLushort> &elements
    ) : ElementModel(shader, nullptr, vertices, elements) {

    }

protected:
    void drawCallback(const Shader &shader) override;
};
