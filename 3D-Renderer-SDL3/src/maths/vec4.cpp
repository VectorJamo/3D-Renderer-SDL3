#include "vec4.h"
namespace sml {
	vec4::vec4()
		:x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	vec4::vec4(float x, float y, float z)
		:x(x), y(y), z(z), w(1.0f)
	{
	}

	vec4::vec4(float x, float y, float z, float w)
		:x(x), y(y), z(z), w(w)
	{
	}

	vec4 vec4::operator+(const vec4& another)
	{
		return vec4(this->x - another.x, this->y - another.y, this->z - another.z);
	}

	vec4 vec4::operator-(const vec4& another)
	{
		return vec4(this->x - another.x, this->y - another.y, this->z - another.z);
	}

	vec4 vec4::operator*(const vec4& another)
	{
		return vec4(this->x * another.x, this->y * another.y, this->z * another.z);
	}

	vec4* vec4::GetLocation()
	{
		return this;
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vec)
	{
		stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
		return stream;
	}
}

