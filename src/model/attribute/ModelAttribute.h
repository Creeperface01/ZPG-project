#ifndef MODELATTRIBUTE_H
#define MODELATTRIBUTE_H

#include <vector>
#include <memory>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../../util/glTypes.h"

class ModelAttribute {
private:
    size_t _size;
    size_t _byteSize;
    size_t _components;
    size_t _componentSize;
    GLenum _type;
    void* _data;

public:
    ModelAttribute(size_t size, size_t byteSize, size_t components, size_t componentSize, GLenum type, void* data);

    [[nodiscard]] size_t getSize() const;

    [[nodiscard]] size_t getByteSize() const;

    [[nodiscard]] size_t getComponents() const;

    [[nodiscard]] size_t getComponentSize() const;

    [[nodiscard]] GLenum getType() const;

    [[nodiscard]] void* getData() const;

    template<typename Entry, typename Type>
    static ModelAttribute from(size_t size, void* data) {
        constexpr auto components = sizeof(Entry) / sizeof(Type);
        static_assert(
            components * sizeof(Type) == sizeof(Entry),
            "Entry type size does not match the component type size"
        );

        return {size / sizeof(Entry), size, components, sizeof(Type), glType<Type>::type, data};
    }

    template<typename T>
    static ModelAttribute from(size_t size, void* data) {
        return from<T, T>(size, data);
    }

    template<typename Entry, typename Type>
    static ModelAttribute from(std::vector<Entry>& data) {
        return from<Entry, Type>(data.size() * sizeof(Entry), data.data());
    }

    template<typename T>
    static ModelAttribute from(std::vector<T>& data) {
        return from<T, T>(data);
    }

    static ModelAttribute from(std::vector<glm::vec4>& data);

    static ModelAttribute from(std::vector<glm::vec3>& data);

    static ModelAttribute from(std::vector<glm::vec2>& data);

    friend class Model;
};


#endif //MODELATTRIBUTE_H
