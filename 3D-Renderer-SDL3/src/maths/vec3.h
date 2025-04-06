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

		vec3 operator+(const vec3& another);
		vec3 operator-(const vec3& another);
		vec3 operator*(const vec3& another);
		
		vec3* GetLocation();
	};

	std::ostream& operator<<(std::ostream& stream, const vec3& vec);
}

