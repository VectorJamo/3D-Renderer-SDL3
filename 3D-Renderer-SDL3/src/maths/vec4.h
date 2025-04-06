#pragma once
#include <iostream>

namespace sml {

	struct vec4
	{
		union
		{
			struct
			{
				float x, y, z, w;
			};
			struct
			{
				float r, g, b, a;
			};
		};

		vec4();
		vec4(float x, float y, float z);
		vec4(float x, float y, float z, float w);

		vec4 operator+(const vec4& another);
		vec4 operator-(const vec4& another);
		vec4 operator*(const vec4& another);

		vec4* GetLocation();
	};

	std::ostream& operator<<(std::ostream& stream, const vec4& vec);
}

