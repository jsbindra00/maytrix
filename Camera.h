#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace nr {
	class Camera {
	private:
		glm::vec3 position_;
		glm::vec3 front_;
		glm::vec3 up_;
		float cameraSpeed_;
	public:
		Camera(const glm::vec3& initPosition);
		void MoveNorth(const float& dT);
		void MoveEast(const float& dT);
		void MoveSouth(const float& dT);
		void MoveWest(const float& dT);
		void MoveUp();
		void MoveDown();
		inline glm::vec3 Position() const noexcept { return position_; }
		inline glm::vec3 Up() const noexcept { return up_; }
		inline glm::vec3 Front() const noexcept { return front_; }
		inline void SetCameraSpeed(const float& speed) { cameraSpeed_ = speed; }
	};
}