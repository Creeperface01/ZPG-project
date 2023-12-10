#include "ElementModel.h"

#include "../util/debug.h"

ElementModel::ElementModel(const std::vector<GLushort>& elements,
                           const std::vector<ModelAttribute>& vertexAttributes): BaseModel(vertexAttributes),
    _elementCount(elements.size()) {
    _vao->use([this, &elements]() {
        _ebo = std::unique_ptr<Buffer>(Buffer::create(Buffer::Type::ELEMENT_ARRAY));
        _ebo->setData(elements);
        this->addBuffer(_ebo.get());
    });
}

void ElementModel::drawCallback(const Shader& shader) const {
    _ebo->use([this] {
        debugGlCall(
            glDrawElements,
            GL_TRIANGLES,
            static_cast<GLsizei>(_elementCount),
            GL_UNSIGNED_SHORT,
            nullptr
        );
    });
}
