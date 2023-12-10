#include "ModelConverter.h"

void ModelConverter::convert(const float *data,
                             size_t dataSize, std::vector<glm::vec3> &vertices,
                             std::vector<glm::vec3> &normals
                             ) {
    struct tuple {
        glm::vec3 pos;
        glm::vec3 norm;
    };

    union {
        const tuple *packed;
        const float *raw;
    } data_union{
            .raw = data
    };

    auto size = dataSize / sizeof(tuple);

    vertices.reserve(size);
    normals.reserve(size);

    for (int i = 0; i < size; ++i) {
        auto &entry = data_union.packed[i];

        vertices.push_back(entry.pos);
        normals.push_back(entry.norm);
    }
}

void ModelConverter::convert(const float *data,
                             size_t dataSize, std::vector<glm::vec3> &vertices,
                             std::vector<glm::vec3> &normals,
                             std::vector<glm::vec2> &uvs
) {
    struct tuple {
        glm::vec3 pos;
        glm::vec3 norm;
        glm::vec2 uv;
    };

    union {
        const tuple *packed;
        const float *raw;
    } data_union{
            .raw = data
    };

    auto size = dataSize / sizeof(tuple);

    vertices.reserve(size);
    normals.reserve(size);
    uvs.reserve(size);

    for (int i = 0; i < size; ++i) {
        auto &entry = data_union.packed[i];

        vertices.push_back(entry.pos);
        normals.push_back(entry.norm);
        uvs.push_back(entry.uv);
    }
}

void ModelConverter::convertDataToVector(const float *data, size_t dataSize, std::vector<glm::vec3> &vector) {
    union {
        const float *raw;
        const glm::vec3 *converted;
    } data_union{
            .raw = data
    };

    auto size = dataSize / sizeof(glm::vec3);
    vector.reserve(size);

    for (int i = 0; i < size; ++i) {
        vector.push_back(data_union.converted[i]);
    }
}
