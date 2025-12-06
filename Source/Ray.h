#pragma once
#include <glm/glm.hpp>
#include "Color.h"

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() = default;
	Ray(glm::vec3 origin, glm::vec3 direction) {
		this->origin = origin;
		this->direction = direction;
	}

	glm::vec3 At(float T) const {
		return origin + (T * direction);
	}
};

struct raycastHit
{
	glm::vec3 point;	// point of ray hit
	glm::vec3 normal;	// normal of surface hit
	float distance;	// distance from ray origin to hit

	color3_t color;	// hit object material
};