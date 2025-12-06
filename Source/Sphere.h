#pragma once
#include "Object.h"
#include "Ray.h"
class Sphere : public Object
{
public:
	Sphere() = default;
	Sphere(const glm::vec3& position, float radius, const color3_t& color) :
		Object(color),// <call Object constructor using color as parameter>,
		position{position},
		radius{radius}
	{ }

	bool Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit& raycastHit) override;

public:
	glm::vec3 position;
	float radius{ 0 };
};
