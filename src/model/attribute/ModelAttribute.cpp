#include "ModelAttribute.h"

ModelAttribute::ModelAttribute(
    size_t size,
    size_t byteSize,
    size_t components,
    size_t componentSize,
    GLenum type,
    void* data
): _size(size),
   _byteSize(byteSize),
   _components(components),
   _componentSize(componentSize),
   _type(type),
   _data(data) {
}

size_t ModelAttribute::getSize() const {
    return _size;
}

size_t ModelAttribute::getByteSize() const {
    return _byteSize;
}

size_t ModelAttribute::getComponents() const {
    return _components;
}

size_t ModelAttribute::getComponentSize() const {
    return _componentSize;
}

GLenum ModelAttribute::getType() const {
    return _type;
}

void* ModelAttribute::getData() const {
    return _data;
}

ModelAttribute ModelAttribute::from(std::vector<glm::vec4>& data) {
    return from<glm::vec4, glm::vec4::value_type>(data);
}

ModelAttribute ModelAttribute::from(std::vector<glm::vec3>& data) {
    return from<glm::vec3, glm::vec3::value_type>(data);
}

ModelAttribute ModelAttribute::from(std::vector<glm::vec2>& data) {
    return from<glm::vec2, glm::vec2::value_type>(data);
}
