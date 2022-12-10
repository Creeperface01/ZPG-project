#include "DrawableObject.h"

DrawableObject::DrawableObject(BaseModel *model) : _model(model) {

}

void DrawableObject::draw() {
    auto matrix = glm::mat4(1.0f);

    if (_scaleTransform.has_value()) {
        matrix = _scaleTransform->transform(matrix);
    }

    if (_rotateTransform.has_value()) {
        matrix = _rotateTransform->transform(matrix);
    }

    if (_translateTransform.has_value()) {
        matrix = _translateTransform->transform(matrix);
    }

    _model->draw(
            matrix
    );
}

void DrawableObject::setPosition(const glm::vec3 &position) {
    _translateTransform = TranslateTransform(position);
}

void DrawableObject::setRotation(const glm::vec3 &axis, float angle) {
    setRotation(axis, glm::zero<glm::vec3>(), angle);
}

void DrawableObject::setRotation(const glm::vec3 &axis, const glm::vec3 &center, float angle) {
    _rotateTransform = RotateTransform(axis, center, angle);
//    if (center == glm::zero<glm::vec3>()) {
//        _rotateTransform = RotateTransform(axis, center, angle);
//        return;
//    }
}

void DrawableObject::setPositionAndRotation(
        const glm::vec3 &position,
        float angle,
        const glm::vec3 &center,
        const glm::vec3 &axis
) {

}

void DrawableObject::setScale(const glm::vec3 &scale) {
    this->_scaleTransform = ScaleTransform(scale);
}
