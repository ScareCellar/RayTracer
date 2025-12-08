#pragma once
#include "Object.h"
#include "Ray.h"
class Sphere : public Object
{
public:
	Sphere() = default;
	Sphere(const Transform& transform, float radius, std::shared_ptr<Material> material) :
		Object(transform, material),// <call Object constructor using color as parameter>,
		radius{radius}
	{ }

	bool Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit& raycastHit) override;

public:
	float radius{ 0 };
};
