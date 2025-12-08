#include "Sphere.h"

bool Sphere::Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit& raycastHit) {
    // compute direction vector (ray origin - sphere center)
    glm::vec3 oc = ray.origin - transform.position;

    // quadratic coefficients for ray–sphere intersection
    // a coefficient is a number that multiplies a variable in a mathematical expression
    // for example: 3x + 5 <= the coefficient of x is 3
    float a = glm::dot(ray.direction, ray.direction);// dot product of ray direction and ray direction
    float b = 2 * glm::dot(ray.direction, oc);// 2 * dot product of ray.direction and oc
    float c = glm::dot(oc, oc) - (radius * radius);// dot product of oc and oc - radius squared

    // discriminant tells us how many real intersection points exist :
    // discriminant => b² - 4ac
    // b² = (b * b)
    float discriminant = (b * b) - (4 * a * c); // b squared - 4 * a * c

    // discriminant of quadratic: < 0 no hit, = 0 tangent (one hit), > 0 two hits
    if (discriminant >= 0) {
        // quadratic formula gives possible ray–sphere intersection distances.
        // t = (-b ± sqrt(discriminant)) / (2a)

        // solve quadratic for the nearest intersection: t = (-b - sqrt(discriminant)) / (2a)
        // use the smaller root first (closest hit along the ray).
        float t = (-b - sqrt(discriminant)) / (2 * a);//(-b - sqrt(discriminant)) / (2a)
        if (t > minDistance && t < maxDistance) {
            raycastHit.distance = t;// t is the distance
            raycastHit.point = ray.At(t);// use ray at(t)
            raycastHit.normal = (raycastHit.point - transform.position) / radius;

            raycastHit.color = material->GetColor();

            return true;
        }
        // if the nearest root wasn't valid, check the second one: t = (-b + sqrt(discriminant)) / (2a)
        // this is the farther intersection point where the ray exits the sphere.
        t = (-b + sqrt(discriminant)) / (2 * a);//(-b + sqrt(discriminant)) / (2a)
        if (t > minDistance && t < maxDistance) {
            raycastHit.distance = t;// t is the distance
            raycastHit.point = ray.At(t);// use ray at(t)
            raycastHit.normal = (raycastHit.point - transform.position) / radius;

            raycastHit.color = material->GetColor();

            return true;
        }
    }

    return false;
}
