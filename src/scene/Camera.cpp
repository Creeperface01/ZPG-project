#include "Camera.h"

#include "../window/Window.h"
#include "../util/util.h"

Camera::Camera(Window &window, const glm::vec3 &position) :
        _eye(position),
        _cameraOffset(-_eye) {
    auto cursor = window.getCursor();

    cursor->attach(this);

    Keyboard::HOLD.attach(this);
    Keyboard::PRESS.attach(this);
}

void Camera::update(Cursor *subject) {
    float xOffset = subject->getX() - subject->getLastX();
    float yOffset = subject->getLastY() - subject->getY();

    xOffset *= 0.1f;
    yOffset *= 0.1f;

    _yaw += xOffset;
    _pitch += yOffset;

    if (_pitch > 89.0f)
        _pitch = 89.0f;

    if (_pitch < -89.0f)
        _pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    direction.y = sin(glm::radians(_pitch));
    direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

    _cameraOffset = glm::normalize(direction);

    _dirty = true;
}

void Camera::update(Keyboard::Press *subject) {
    updateMovement(subject->_code);
}

void Camera::update(Keyboard::Hold *subject) {
    updateMovement(subject->_code);
}

void Camera::updateMovement(const Keyboard::KeyCode &keyCode) {
    if (keyCode == KeyCodes::w) {
        _motion = glm::normalize(_cameraOffset);
    } else if (keyCode == KeyCodes::s) {
        _motion = -glm::normalize(_cameraOffset);
    } else if (keyCode == KeyCodes::a) {
        _motion = -glm::normalize(glm::cross(_cameraOffset, glm::vec3(0, 1, 0)));
    } else if (keyCode == KeyCodes::d) {
        _motion = glm::normalize(glm::cross(_cameraOffset, glm::vec3(0, 1, 0)));
    }

    _motion *= 0.1f;

    _dirty = true;
}

void Camera::update() {
    if (_motion != glm::zero<glm::vec3>()) {
        _eye += _motion;

        _motion *= 0.98f;

        if (glm::length(_motion) < 0.01) {
            _motion = glm::zero<glm::vec3>();
        }

        _dirty = true;
    }
}

void Camera::recalculateMatrices() {
    if (!_dirty) {
        return;
    }

    _viewMatrix = glm::lookAt(
            _eye, // Camera is at (4,3,-3), in World Space
            _eye + _cameraOffset, // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    _projectionMatrix = glm::perspective(
            glm::radians(_fov),
            4.0f / 3.0f,
            0.01f,
            _renderDistance
    );

    _dirty = false;
}

float Camera::getFov() const {
    return _fov;
}

float Camera::getYaw() const {
    return _yaw;
}

float Camera::getPitch() const {
    return _pitch;
}

const glm::vec3 &Camera::getEye() const {
    return _eye;
}

const glm::vec3 &Camera::getMotion() const {
    return _motion;
}

void Camera::setFov(float fov) {
    _fov = fov;
}

void Camera::setYaw(float yaw) {
    _yaw = yaw;
}

void Camera::setPitch(float pitch) {
    _pitch = pitch;
}

void Camera::setEye(const glm::vec3 &eye) {
    _eye = eye;
}

void Camera::setMotion(const glm::vec3 &motion) {
    _motion = motion;
}

const glm::mat4 &Camera::getViewMatrix() const {
    return _viewMatrix;
}

const glm::mat4 &Camera::getProjectionMatrix() const {
    return _projectionMatrix;
}

[[maybe_unused]] float Camera::getRenderDistance() const {
    return _renderDistance;
}

void Camera::setRenderDistance(float renderDistance) {
    _renderDistance = renderDistance;
}
