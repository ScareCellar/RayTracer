#pragma once
#include "Transform.h"
#include "Material.h"
#include <memory>
class Object
{
public:
	Object() = default;
	Object(const Transform& transform, std::shared_ptr<Material> material) :
		transform{ transform },
		material{ material }
	{
	}
	Object(color3_t color) :
		color{color}
	{ }

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit& raycastHit) = 0;

protected:
	Transform transform;
	std::shared_ptr<Material> material;
	color3_t color;
};