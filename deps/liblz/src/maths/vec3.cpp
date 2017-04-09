#include "maths.h"

using namespace lz;
using namespace maths;

vec3::vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vec3::vec3(vec3* vec)
{
	this->x = vec->x;
	this->y = vec->y;
	this->z = vec->z;
}

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void vec3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float vec3::magnitude()
{
	return (SQRT(x * x + y * y + z * z));
}

vec3 vec3::normalize()
{
	vec3 result;
	float m = magnitude();
	result.set(x / m, y / m, z / m);

	return (result);
}

vec3 vec3::cross(vec3 r)
{
	vec3 result;

	result.x = y * r.z - z * r.y;
	result.y = z * r.x - x * r.z;
	result.z = x * r.y - y * r.x;

	return (result);
}

vec3 vec3::rotate(quat rot)
{
	quat w = rot.mul(this);
	w = w.mul(rot.conjugate());

	return (vec3(w.x, w.y, w.z));
}

float vec3::distance(vec3 a, vec3 b)
{
	return (vec3(a).sub(b).magnitude());
}

float vec3::dot(vec3 r)
{
	return (x * r.x + y * r.y + z * r.z);
}

vec3 vec3::reflect(vec3 normal)
{
	return (sub(normal.copy().mul(dot(normal) * 2.0f)));
}
