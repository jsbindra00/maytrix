#include "Camera.h"
nr::Camera::Camera(const glm::vec3& initPosition)
	:position_(initPosition),
	up_(0.0f,1.0f,0.0f),
	front_(0.0f,0.0f,-1.0f),
	cameraSpeed_(0.1f)
{

}
void nr::Camera::MoveNorth(const float& dT)
{
	position_ = position_ + cameraSpeed_ * front_;
}

void nr::Camera::MoveEast(const float& dT)
{
	position_ -= cameraSpeed_ * glm::normalize(glm::cross(front_, up_));
}

void nr::Camera::MoveSouth(const float& dT)
{
	position_ -= cameraSpeed_ * front_;
}

void nr::Camera::MoveWest(const float& dT)
{
	position_ += cameraSpeed_ * glm::normalize(glm::cross(front_, up_));
}

void nr::Camera::MoveUp()
{
	position_ += cameraSpeed_ * up_;
}
void nr::Camera::MoveDown()
{
	position_ -= cameraSpeed_ * up_;
}

