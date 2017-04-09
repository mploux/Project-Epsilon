#include "maths.h"

using namespace lz;
using namespace maths;

quat::quat()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 1;
}

quat::quat(quat* q)
{
	this->x = q->x;
	this->y = q->y;
	this->z = q->z;
	this->w = q->w;
}

quat::quat(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void quat::set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

quat::quat(vec3 axis, float angle)
{
	float s = SIN(angle / 2.0f);
	float c = COS(angle / 2.0f);

	this->x = axis.x * s;
	this->y = axis.y * s;
	this->z = axis.z * s;
	this->w = c;
}

float quat::magnitude()
{
	return (SQRT(x * x + y * y + z * z + w * w));
}

quat quat::normalize()
{
	quat result;
	float mag = magnitude();
	result.set(x / mag, y / mag, z / mag, w / mag);

	return (result);
}

quat quat::conjugate()
{
	quat result;
	result.set(-x, -y, -z, w);

	return (result);
}

quat quat::mul(quat r)
{
	quat result;

	result.w = w * r.w - x * r.x - y * r.y - z * r.z;
	result.x = x * r.w + w * r.x + y * r.z - z * r.y;
	result.y = y * r.w + w * r.y + z * r.x - x * r.z;
	result.z = z * r.w + w * r.z + x * r.y - y * r.x;

	return (result);
}

quat quat::mul(vec3 r)
{
	quat result;

	result.w = -x * r.x - y * r.y - z * r.z;
	result.x = w * r.x + y * r.z - z * r.y;
	result.y = w * r.y + z * r.x - x * r.z;
	result.z = w * r.z + x * r.y - y * r.x;

	return (result);
}

float quat::dot(quat r)
{
	return (x * r.x + y * r.y + z * r.z + w * r.w);
}

mat4 quat::to_matrix()
{
	vec3 forward(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
	vec3 up(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
	vec3 right(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));

	return (mat4::rotate(forward, up, right));
}

vec3 quat::getForward()
{
	vec3 result(0, 0, 1);
	result = result.rotate(this);

	return (result);
}

vec3 quat::getBack()
{
	vec3 result(0, 0, -1);
	result = result.rotate(this);

	return (result);
}

vec3 quat::getRight()
{
	vec3 result(1, 0, 0);
	result = result.rotate(this);

	return (result);
}

vec3 quat::getLeft()
{
	vec3 result(-1, 0, 0);
	result = result.rotate(this);

	return (result);
}

vec3 quat::getUp()
{
	vec3 result(0, 1, 0);
	result = result.rotate(this);

	return (result);
}

vec3 quat::getDown()
{
	vec3 result(0, -1, 0);
	result = result.rotate(this);

	return (result);
}
