#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../util/Observer.h"
#include "../util/Observable.h"
#include "../io/Cursor.h"
#include "../io/Keyboard.h"

class Scene;

class Camera : Observer<Cursor*>, Observer<Keyboard::Press*>, Observer<Keyboard::Hold*>, public Observable<Camera> {
private:
    Scene *_scene;

    float _fov = 45;

    float _renderDistance = 100;

    float _yaw = 180, _pitch = 0;

    bool _dirty = true;

    glm::vec3 _eye;
    glm::vec3 _cameraDirection;

    glm::vec3 _motion = glm::zero<glm::vec3>();

    glm::mat4 _viewMatrix{};

    glm::mat4 _projectionMatrix{};

    void updateMovement(const Keyboard::KeyCode &keyCode);

public:
    explicit Camera(
            Scene *scene,
            const glm::vec3 &position
    );

    void update();

    void update(Cursor *subject) override;

    void update(Keyboard::Press *subject) override;

    void update(Keyboard::Hold *subject) override;

    void recalculateMatrices();

    [[nodiscard]] float getFov() const;

    void setFov(float fov);

    [[nodiscard]] float getYaw() const;

    void setYaw(float yaw);

    [[nodiscard]] float getPitch() const;

    void setPitch(float pitch);

    [[nodiscard]] const glm::vec3 &getEye() const;

    void setEye(const glm::vec3 &eye);

    [[nodiscard]] const glm::vec3 &getMotion() const;

    void setMotion(const glm::vec3 &motion);

    [[nodiscard]] const glm::mat4 &getViewMatrix() const;

    [[nodiscard]] const glm::mat4 &getProjectionMatrix() const;

    [[maybe_unused]] float getRenderDistance() const;

    void setRenderDistance(float renderDistance);

    void pointAt(const glm::vec3 &position);

    void setDirection(const glm::vec3 &direction);

    glm::vec3 getDirection() const;

    glm::vec3 getCursorVector() const;
};
