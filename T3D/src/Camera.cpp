#include "Camera.h"

#include "glm/gtx/transform.hpp"

#include <iostream>

using namespace std;

// Camera constructor
Camera::Camera(){
								std::cout << "(Camera.cpp) Constructor called\n";
								eyePosition = glm::vec3(0.0f,0.0f, 30.0f); // FIX: Typically this should be 0,0,0, but I moved for our assignment.
								viewDirection = glm::vec3(0.0f,0.0f, 1.0f);
								upVector = glm::vec3(0.0f, 1.0f, 0.0f);

}

void Camera::mouseLook(int mouseX, int mouseY){
								// Record our new position as a vector
								glm::vec2 newMousePosition(mouseX, mouseY);
								// Detect how much the mouse has moved since
								// the last time
								glm::vec2 mouseDelta = 0.005f*(newMousePosition-oldMousePosition);
								viewDirection = glm::mat3(glm::rotate(-mouseDelta.x, upVector)) *
																								viewDirection;

								// Update our old position after we have made changes
								oldMousePosition = newMousePosition;
}

glm::vec2 Camera::getMouseDelta(int mouseX, int mouseY) {
								glm::vec2 newMousePosition(mouseX, mouseY);
								// Detect how much the mouse has moved since
								// the last time
								glm::vec2 mouseDelta = 0.01f*(newMousePosition-oldMousePosition);
								oldMousePosition = newMousePosition;
								return mouseDelta;

}

void Camera::rotateBoard(int mouseX, int mouseY, glm::vec3 boardCenter, float cameraDistance) {
								cout << " " << getEyeXPosition() << " " << getEyeYPosition() << " " << getEyeZPosition() <<  "  " <<  endl;
								glm::vec2 newMousePosition(mouseX, mouseY);
								glm::vec2 mouseDelta = 0.01f*(newMousePosition-oldMousePosition);

								// float eyePositionX = boardCenter.x + cameraDistance * cos(mouseDelta.x );
								// float eyePositionZ = boardCenter.z + cameraDistance * sin(mouseDelta.x );
								warpCamera(glm::vec3(boardCenter.x + (cameraDistance * cos(mouseDelta.x)), boardCenter.y, boardCenter.z - (cameraDistance * sin(mouseDelta.x))));

								viewDirection = glm::mat3(glm::rotate(-mouseDelta.x, upVector)) * viewDirection;

								//float eyePositionX = eyePositionX + 1;
								//float eyePositionY = eyePositionY + 1;


								oldMousePosition = newMousePosition;
}

void Camera::warpCamera(glm::vec3 newPosition) {
								eyePosition = newPosition;
}

void Camera::moveForward(float speed){
								eyePosition.z -= speed;
}

void Camera::moveBackward(float speed){
								eyePosition.z += speed;
}

void Camera::moveLeft(float speed){
								eyePosition.x -= speed;
}

void Camera::moveRight(float speed){
								eyePosition.x += speed;
}

void Camera::moveUp(float speed){
								eyePosition.y += speed;
}

void Camera::moveDown(float speed){
								eyePosition.y -= speed;
}

float Camera::getEyeXPosition(){
								return eyePosition.x;
}

float Camera::getEyeYPosition(){
								return eyePosition.y;
}

float Camera::getEyeZPosition(){
								return eyePosition.z;
}

float Camera::getViewXDirection(){
								return viewDirection.x;
}

float Camera::getViewYDirection(){
								return viewDirection.y;
}

float Camera::getViewZDirection(){
								return viewDirection.z;
}

// Get our view matrix from this camera
glm::mat4 Camera::getWorldToViewmatrix() const {
								// Think about the second argument and why that is
								// setup as it is.
								return glm::lookAt( eyePosition,
																												eyePosition + viewDirection,
																												upVector);
}
