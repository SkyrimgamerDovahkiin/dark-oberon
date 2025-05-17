#include "docamera.hpp"

Camera::Camera()
{
}

Camera::~Camera()
{
}

/**
 *  Creates the Camera.
 */
void Camera::Create()
{
    mEye = glm::vec3(10.0f, 10.0f, 10.0f);
    mCameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);

    mCameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    mCameraDirection = glm::normalize(mCameraPos - mCameraTarget);
    mCameraRight = glm::normalize(glm::cross(mUp, mCameraDirection));
    mCameraUp = glm::cross(mCameraDirection, mCameraRight);
    // mView = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    mScreenWidth = (480.0f * 2.0f);
    mScreenHeight = (420.0f * 2.0f);
}

/**
 *  Is called everytime an event happens. Events that want to be used need to be dispatched
 *  @param e                The Event, can be every event.
 */
void Camera::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Camera::Translate, this, std::placeholders::_1));
    dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&Camera::Zoom, this, std::placeholders::_1));
}

/**
 *  Moves the Camera.
 *  @param e                The KeyPressedEvent that contains all the key pressed stuff.
 */
bool Camera::Translate(KeyPressedEvent &e)
{
    float cameraSpeed = 4.0f * mDeltaTime;

    if (e.GetKeyCode() == GLFW_KEY_W && e.GetRepeatCount() == 1)
    {
        mCameraPos.y -= 1.0f * cameraSpeed;
    }
    if (e.GetKeyCode() == GLFW_KEY_S && e.GetRepeatCount() == 1)
    {
        mCameraPos.y += 1.0f * cameraSpeed;
    }
    if (e.GetKeyCode() == GLFW_KEY_A && e.GetRepeatCount() == 1)
    {
        mCameraPos.x -= 1.0f * cameraSpeed;
    }
    if (e.GetKeyCode() == GLFW_KEY_D && e.GetRepeatCount() == 1)
    {
        mCameraPos.x += 1.0f * cameraSpeed;
    }
    return false;
}

/**
 *  Handles zoom.
 *  @param e                The MouseScrolledEvent that contains all the mouse scrolled stuff.
 */
bool Camera::Zoom(MouseScrolledEvent &e)
{
    mZoomLevel -= e.GetYOffset() * 2.0f;

    // Clamp zoom level to a minimum and maximum
    const float minZoom = 1.0f; // closest allowed zoom
    const float maxZoom = 5.0f; // farthest allowed zoom

    if (mZoomLevel < minZoom)
        mZoomLevel = minZoom;
    if (mZoomLevel > maxZoom)
        mZoomLevel = maxZoom;

    SetProjection((480.0f * 2.0f), (420.0f * 2.0f)); // or pass in actual viewport size

    // Debug((char*)std::to_string(mFov).c_str());

    // SetProjection(mFov, (480.0f * 2.0f), (420.0f * 2.0f));

    return false;
}

/**
 *  Sets the cameras projection matrix.
 *  @param width                The width.
 *  @param height                The height.
 */
void Camera::SetProjection(float width, float height)
{
    // mProjection = glm::perspective(glm::radians(fovy), width / height, 0.1f, 100.0f);

    float aspectRatio = width / height;

    float halfWidth = (aspectRatio * mZoomLevel) * 0.5f;
    float halfHeight = mZoomLevel * 0.5f;

    mProjection = glm::ortho(
        -halfWidth, +halfWidth,   // left to right
        -halfHeight, +halfHeight, // bottom to top
        -100.0f, 100.0f           // near to far
    );

    // float halfWidth = (width / 2.0f) * mZoomLevel;
    // float halfHeight = (height / 2.0f) * mZoomLevel;

    // // mProjection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -100.0f, 100.0f);

    // // float baseSize = 10.0f; // or whatever you want 1.0 zoom to show
    // // float aspectRatio = width / height;

    // // float scale = 1.0f / mZoomLevel;

    // // float halfWidth = baseSize * aspectRatio * scale;
    // // float halfHeight = baseSize * scale;

    // float aspectRatio = width / height;

    // mProjection = glm::ortho(0.0f, aspectRatio * mZoomLevel, mZoomLevel, 0.0f, -100.0f, 100.0f);
    // mViewProj = mProjection * mView;
}

/**
 *  Does the proper calculations and return the view matrix.
 *  @param width                The width.
 *  @param height                The height.
 */
glm::mat4 &Camera::GetView()
{
    mView = glm::mat4(1.0f);

    // Translate camera position into view matrix
    mView = glm::translate(mView, -mCameraPos);

    // Rotate for isometric effect
    mView = glm::rotate(mView, glm::radians(35.264f), glm::vec3(1, 0, 0)); // tilt down
    mView = glm::rotate(mView, glm::radians(45.0f), glm::vec3(0, 1, 0));   // rotate around Y

    return mView;
}
