#include "Camera.h"

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	this->eye = eye;

	// create camera axis
	this->forward = glm::normalize(target - eye);
	this->right = glm::normalize(glm::cross(forward, up));
	this->up = glm::normalize(glm::cross(right, forward));

	CalculateViewPlane();
}

Ray Camera::GetRay(const glm::vec2& uv) const {
	Ray ray;

	ray.origin = this->eye;
	ray.direction = lowerLeft + horizontal * uv.x + vertical * uv.y - eye;

	return ray;
}

void Camera::CalculateViewPlane() {
	float theta = glm::radians(fov);

	float halfHeight = glm::tan(theta / 2);
	float halfWidth = halfHeight * aspectRatio;

	horizontal = right * (halfWidth * 2);
	vertical = up * (halfHeight * 2);

	lowerLeft = eye - (horizontal / 2.0f) - (vertical / 2.0f) + forward;
}

