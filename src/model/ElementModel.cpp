#include "ElementModel.h"

#include "../util/debug.h"

void ElementModel::drawCallback(const Shader &shader) {
    debugGlCall(
            glDrawElements,
            GL_TRIANGLES,
            static_cast<GLsizei>(_elementCount),
            GL_UNSIGNED_SHORT,
            nullptr
    );
}
