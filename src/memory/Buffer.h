#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <string>
#include <mutex>
#include <vector>

#include "../util/exceptions.h"
#include "../util/util.h"
#include "../util/Usable.h"
#include "../util/Noncopyable.h"

class Buffer : public Usable<Buffer>, public Noncopyable {
public:
    enum class Type : GLenum {
        VERTEX_ARRAY = 0,
        ARRAY = GL_ARRAY_BUFFER,
        ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
    };

private:
    Type _type;

    static std::unordered_map<Type, std::mutex> _bindLock;

protected:
    GLuint _id;

    explicit Buffer(Type type);

    virtual void generate(GLuint &id) const;

    virtual void bind() const;

    virtual void unbind() const;

public:
    static Buffer *create(const Type &type);

    ~Buffer() override;

    [[nodiscard]] Type getType() const;

    void startUsing() override;

    void stopUsing() override;

    void setData(size_t size, const void *data);

    template<typename T>
    void setData(const std::vector<T> &data) {
        setData(
                get_vector_size(data),
                static_cast<const void *>(data.data())
        );
    }
};
