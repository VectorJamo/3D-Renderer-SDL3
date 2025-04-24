#pragma once
#include <iostream>

namespace sml {

	struct vec3
	{
		union
		{
			struct
			{
				float x, y, z;
			};
			struct  
			{
				float r, g, b;
			};
		};

		vec3();
		vec3(float x, float y, float z);

		static vec3 CrossProduct(const vec3& vec1, const vec3& vec2);

		vec3 operator+(const vec3& another) const;
		vec3 operator-(const vec3& another) const;
		vec3 operator*(const vec3& another) const;
		vec3 operator*(float scalar) const;

		float GetMagnitude() const;
		vec3 GetNormalized() const;
		vec3* GetLocation();
	};

	std::ostream& operator<<(std::ostream& stream, const vec3& vec);
}

