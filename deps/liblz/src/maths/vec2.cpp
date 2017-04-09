#include "maths.h"

using namespace lz;
using namespace maths;

vec2::vec2()
{
	this->x = 0;
	this->y = 0;
}

vec2::vec2(vec2* vec)
{
	this->x = vec->x;
	this->y = vec->y;
}

vec2::vec2(float x, float y, float z)
{
	this->x = x;
	this->y = y;
}

void vec2::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
}

float vec2::magnitude()
{
	return (SQRT(x * x + y * y + z * z));
}

vec2 vec2::normalize()
{
	vec2 result;
	float m = magnitude();
	result.set(x / m, y / m);

	return (result);
}