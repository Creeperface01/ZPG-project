#include "Camera.h"

#include "../window/Window.h"
#include "../scene/Scene.h"
#include "../util/util.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

Camera::Camera(Scene* scene, const glm::vec3& position) : _scene(scene),
                                                          _eye(position),
                                                          _cameraDirection(-_eye) {
    auto cursor = scene->getWindow()->getCursor();

    cursor->attach(this);

    Keyboard::HOLD.attach(this);
    Keyboard::PRESS.attach(this);
}

void Camera::update(Cursor* subject) {
    if (!_scene->isActive()) {
        return;
    }

    if (subject->getMode() != Cursor::Mode::DISABLED) {
        return;
    }

    float xOffset = subject->getX() - subject->getLastX();
    float yOffset = subject->getLastY() - subject->getY();

    xOffset *= 0.1f;
    yOffset *= 0.1f;

    _yaw -= xOffset;
    _pitch += yOffset;

    if (_pitch > 89.0f)
        _pitch = 89.0f;

    if (_pitch < -89.0f)
        _pitch = -89.0f;

    float pitchRadians = glm::radians(_pitch);
    float yawRadians = glm::radians(_yaw);

    glm::vec3 direction;
    direction.x = cos(yawRadians) * cos(pitchRadians);
    direction.y = sin(pitchRadians);
    direction.z = sin(-yawRadians) * cos(pitchRadians);

    _cameraDirection = glm::normalize(direction);

    _dirty = true;
}

void Camera::update(Keyboard::Press* subject) {
    if (!_scene->isActive()) {
        return;
    }

    updateMovement(subject->_code);
}

void Camera::update(Keyboard::Hold* subject) {
    if (!_scene->isActive()) {
        return;
    }

    updateMovement(subject->_code);
}

void Camera::updateMovement(const Keyboard::KeyCode& keyCode) {
    if (keyCode == KeyCodes::w) {
        _motion = glm::normalize(_cameraDirection);
    } else if (keyCode == KeyCodes::s) {
        _motion = -glm::normalize(_cameraDirection);
    } else if (keyCode == KeyCodes::a) {
        _motion = -glm::normalize(glm::cross(_cameraDirection, glm::vec3(0, 1, 0)));
    } else if (keyCode == KeyCodes::d) {
        _motion = glm::normalize(glm::cross(_cameraDirection, glm::vec3(0, 1, 0)));
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
        _eye,
        _eye + _cameraDirection,
        glm::vec3(0, 1, 0)
    );

    auto windowProperties = _scene->getWindow()->getProperties();
    _projectionMatrix = glm::perspective(
        glm::radians(_fov),
        static_cast<float>(windowProperties.width) / static_cast<float>(windowProperties.height),
        0.01f,
        _renderDistance
    );

    _dirty = false;

    notifyObservers();
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

const glm::vec3& Camera::getEye() const {
    return _eye;
}

const glm::vec3& Camera::getMotion() const {
    return _motion;
}

void Camera::setFov(float fov) {
    _fov = fov;
    _dirty = true;
}

void Camera::setYaw(float yaw) {
    _yaw = yaw;
    _dirty = true;
}

void Camera::setPitch(float pitch) {
    _pitch = pitch;
    _dirty = true;
}

void Camera::setEye(const glm::vec3& eye) {
    _eye = eye;
    _dirty = true;
}

void Camera::setMotion(const glm::vec3& motion) {
    _motion = motion;
    _dirty = true;
}

const glm::mat4& Camera::getViewMatrix() const {
    return _viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const {
    return _projectionMatrix;
}

[[maybe_unused]] float Camera::getRenderDistance() const {
    return _renderDistance;
}

void Camera::setRenderDistance(float renderDistance) {
    _renderDistance = renderDistance;
}

void Camera::pointAt(const glm::vec3& position) {
    setDirection(position - _eye);
}

void Camera::setDirection(const glm::vec3& direction) {
    auto normalized = glm::normalize(direction);

    setPitch(glm::degrees(asin(-normalized.y)));
    setYaw(glm::degrees(atan2(normalized.x, normalized.z)) - 90);

    _cameraDirection = normalized;
}

glm::vec3 Camera::getDirection() const {
    return _cameraDirection;
}

glm::vec3 Camera::getCursorVector() const {
    auto windowProperties = _scene->getWindow()->getProperties();

    float centerX = static_cast<float>(windowProperties.width) / static_cast<float>(2);
    float centerY = static_cast<float>(windowProperties.height) / static_cast<float>(2);

    GLfloat depth;
    debugGlCall(
        glReadPixels,
        centerX,
        centerY,
        1,
        1,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        &depth
    );

    glm::vec3 screenX = glm::vec3(centerX, centerY, depth);
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec4 viewPort = glm::vec4(0, 0, windowProperties.width, windowProperties.height);
    glm::vec3 pos = glm::unProject(screenX, _viewMatrix, _projectionMatrix, viewPort);

    return pos;
}
