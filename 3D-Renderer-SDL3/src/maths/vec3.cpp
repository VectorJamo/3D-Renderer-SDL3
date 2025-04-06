#include "vec3.h"

namespace sml {
	vec3::vec3()
		:x(0.0f), y(0.0f), z(0.0f)
	{
	}
	vec3::vec3(float x, float y, float z)
		:x(x), y(y), z(z)
	{

	}

	vec3 vec3::operator+(const vec3& another)
	{
		return vec3(this->x + another.x, this->y + another.y, this->z + another.z);
	}

	vec3 vec3::operator-(const vec3& another)
	{
		return vec3(this->x - another.x, this->y - another.y, this->z - another.z);
	}

	vec3 vec3::operator*(const vec3& another)
	{
		return vec3(this->x * another.x, this->y * another.y, this->z * another.z);
	}

	vec3* vec3::GetLocation()
	{
		return this;
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vec)
	{
		stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return stream;
	}
}
