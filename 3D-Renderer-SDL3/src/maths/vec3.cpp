#include "vec3.h"

#include <cmath>

namespace sml {
	vec3::vec3()
		:x(0.0f), y(0.0f), z(0.0f)
	{
	}
	vec3::vec3(float x, float y, float z)
		:x(x), y(y), z(z)
	{

	}

	vec3 vec3::CrossProduct(const vec3& vec1, const vec3& vec2)
	{
		vec3 cross;
		cross.x = vec1.y * vec2.z - vec2.y * vec1.z;
		cross.y = -(vec1.x * vec2.z - vec2.x * vec1.z);
		cross.z = vec1.x * vec2.y - vec1.y * vec2.x;

		return cross;
	}

	vec3 vec3::operator+(const vec3& another) const
	{
		return vec3(this->x + another.x, this->y + another.y, this->z + another.z);
	}

	vec3 vec3::operator-(const vec3& another) const
	{
		return vec3(this->x - another.x, this->y - another.y, this->z - another.z);
	}

	vec3 vec3::operator*(const vec3& another) const
	{
		return vec3(this->x * another.x, this->y * another.y, this->z * another.z);
	}

	vec3 vec3::operator*(float scalar) const
	{
		return vec3(x*scalar, y*scalar, z*scalar);
	}

	float vec3::GetMagnitude() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	vec3 vec3::GetNormalized() const
	{
		float magnitude = GetMagnitude();
		float nX = x / magnitude;
		float nY = y / magnitude;
		float nZ = z / magnitude;

		return vec3(nX, nY, nZ);
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
