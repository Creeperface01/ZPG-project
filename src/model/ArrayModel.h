#pragma once

#include "BaseModel.h"

#include <exception>

class ArrayModel : public BaseModel {
private:
    size_t _vertexCount;

public:

    template<typename T>
    ArrayModel(
            Shader *shader,
            Texture *texture,
            const std::initializer_list<std::vector<T>> &vertexAttributes
    ) : BaseModel(shader) {
        if (vertexAttributes.size() == 0) {
            throw std::runtime_error("Cannot create array model with no vertex attributes");
        }

        _vertexCount = (*vertexAttributes.begin()).size();
        assert(_vertexCount > 0 && "Invalid vertex count");

        _vao->use([this, &vertexAttributes]() {
            int i = 0;
            for (const auto &attribute: vertexAttributes) {
                auto buffer = Buffer::create(Buffer::Type::ARRAY);
                buffer->setData(attribute);

                this->addAttributeBuffer(buffer, i++, 3); //TODO: dynamic component size
            }
        });
    }

    template<typename T>
    ArrayModel(
            Shader *shader,
            const std::initializer_list<std::vector<T>> &vertexAttributes
    ) : ArrayModel(shader, nullptr, vertexAttributes) {
    }

protected:
    void drawCallback(const Shader &shader) override;
};
