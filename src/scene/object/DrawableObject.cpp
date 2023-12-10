#include "DrawableObject.h"

#include "component/ConstantColorObjectComponent.h"
#include "component/ModelObjectComponent.h"

DrawableObject::DrawableObject(BaseModel* model, Shader* shader) : DrawableObject(model, shader, {}) {
}

DrawableObject::DrawableObject(
    BaseModel* model,
    Shader* shader,
    const std::vector<ObjectComponent *>& components
) : _model(model), _shader(shader) {
    _components.reserve(components.size());
    std::transform(
        components.begin(),
        components.end(),
        std::back_inserter(_components),
        [](auto component) {
            return std::unique_ptr<ObjectComponent>(component);
        }
    );

    _components.push_back(std::make_unique<ModelObjectComponent>());

    if (!hasComponent<ConstantColorObjectComponent>()) {
        _components.push_back(std::make_unique<ConstantColorObjectComponent>(
            glm::vec3(163, 165, 199) / 256.f
        ));
    }

    for (const auto& item: _components) {
        item->init(this);
    }
}

void DrawableObject::draw() {
    _shader->use([this](Shader& shader) {
        refreshModelMatrix();

        for (const auto& item: _components) {
            item->beforeDraw(this);
        }

        _model->draw(shader);

        for (const auto& item: _components) {
            item->afterDraw(this);
        }
    });
}

size_t DrawableObject::getId() const {
    return _id;
}

void DrawableObject::setTranslation(const glm::vec3& position) {
    _translateTransform = TranslateTransform(position);
    resetModelMatrix();
}

glm::vec3 DrawableObject::getTranslation() const {
    auto matrix = glm::mat4(1.0f);

    if (_translateTransform.has_value()) {
        matrix = _translateTransform->transform(matrix);
    }

    return matrix[3];
}

void DrawableObject::setRotation(const glm::vec3& axis, float angle) {
    _rotateTransform = RotateTransform(axis, getTranslation(), 0, angle);
    resetModelMatrix();
}

void DrawableObject::setRotation(const glm::vec3& axis, float radius, float angle) {
    _rotateTransform = RotateTransform(axis, getTranslation(), 0, angle);
    resetModelMatrix();
}

//void DrawableObject::setRotation(const glm::vec3 &axis, const glm::vec3 &center, float angle) {
//    setRotation(axis, center, 0, angle);
////    if (center == glm::zero<glm::vec3>()) {
////        _rotateTransform = RotateTransform(axis, center, angle);
////        return;
////    }
//}
//
//void DrawableObject::setRotation(const glm::vec3 &axis, const glm::vec3 &center, float radius, float angle) {
//    _rotateTransform = RotateTransform(axis, center, radius, angle);
//}

void DrawableObject::setPositionAndRotation(
    const glm::vec3& position,
    float angle,
    const glm::vec3& center,
    const glm::vec3& axis
) {
}

void DrawableObject::setScale(const glm::vec3& scale) {
    this->_scaleTransform = ScaleTransform(scale);
    resetModelMatrix();
}

void DrawableObject::setScale(float scale) {
    setScale({scale, scale, scale});
}

glm::mat4 DrawableObject::calculateModelMatrix() const {
    auto matrix = glm::mat4(1.f);

    if (_translateTransform.has_value()) {
        matrix = _translateTransform->transform(matrix);
    }

    if (_rotateTransform.has_value()) {
        matrix = _rotateTransform->transform(matrix);
    }

    if (_scaleTransform.has_value()) {
        matrix = _scaleTransform->transform(matrix);
    }

    return matrix;
}

glm::vec3 DrawableObject::getFinalPosition() const {
    auto matrix = calculateModelMatrix();
    return matrix[3];
}

BaseModel* DrawableObject::getModel() const {
    return _model;
}

Shader* DrawableObject::getShader() const {
    return _shader;
}

void DrawableObject::resetModelMatrix() {
    _modelMatrix = std::nullopt;
}

void DrawableObject::refreshModelMatrix() {
    if (!_modelMatrix.has_value()) {
        _modelMatrix = calculateModelMatrix();
    }
}

glm::mat4 DrawableObject::getModelMatrix() {
    refreshModelMatrix();
    return _modelMatrix.value();
}
