#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>

#include "dologs.h"

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "do_key_event.hpp"
#include "do_mouse_event.hpp"

class Camera
{
public:
    Camera();
    ~Camera();
    void Create();
    void OnEvent(Event &e);
    bool Translate(KeyPressedEvent &e);
    bool Zoom(MouseScrolledEvent &e);
    // bool OnWindowResized(WindowResizeEvent &e);

    // This gets the up vector (0.0f, 1.0f, 0.0f), NOT the camera up!
    inline const glm::vec3 &getUp() const { return mUp; }

    // Getter and Setter for mCameraPos
    inline const glm::vec3 &getCameraPos() const { return mCameraPos; }
    inline void setCameraPos(const glm::vec3 &pos) { mCameraPos = pos; }

    // Getter and Setter for mCameraTarget
    inline const glm::vec3 &getCameraTarget() const { return mCameraTarget; }
    inline void setCameraTarget(const glm::vec3 &target) { mCameraTarget = target; }

    // Getter and Setter for mCameraDirection
    inline const glm::vec3 &getCameraDirection() const { return mCameraDirection; }
    inline void setCameraDirection(const glm::vec3 &direction) { mCameraDirection = direction; }

    // Getter and Setter for mCameraFront
    inline const glm::vec3 &getCameraFront() const { return mCameraFront; }
    inline void setCameraFront(const glm::vec3 &front) { mCameraFront = front; }

    // Getter and Setter for mCameraRight
    inline const glm::vec3 &getCameraRight() const { return mCameraRight; }
    inline void setCameraRight(const glm::vec3 &right) { mCameraRight = right; }

    // Getter and Setter for mCameraUp
    inline const glm::vec3 &getCameraUp() const { return mCameraUp; }
    inline void setCameraUp(const glm::vec3 &up) { mCameraUp = up; }

    // sets the delta time
    inline void SetDeltaTime(double deltaTime) { mDeltaTime = deltaTime; }

    void SetProjection(float width, float height);

    // returns projection
    inline glm::mat4 &GetProjection() { return mProjection; }

    inline glm::vec3 &GetEye() { return mEye; }

    glm::mat4 &GetView();

private:
    glm::vec3 mUp;

    glm::vec3 mCameraPos;
    glm::vec3 mCameraTarget;
    glm::vec3 mCameraDirection;
    glm::vec3 mCameraFront;
    glm::vec3 mCameraRight;
    glm::vec3 mCameraUp;
    glm::vec3 mEye;
    // glm::mat4 mView;

    float mCameraSpeed = 0.05f;
    double mDeltaTime = 0.0;

    float mZoomLevel = 1.0f;

    // for zoom/resizing
    float mScreenWidth = 480.0f * 2.0f;
    float mScreenHeight = 420.0f * 2.0f;

    // float mFov = 45.0f;

    glm::mat4 mProjection = glm::mat4(1.0f);
    glm::mat4 mView = glm::mat4(1.0f);
};