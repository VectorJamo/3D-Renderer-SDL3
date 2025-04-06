#pragma once

#include "vec4.h"
#include "vec3.h"

#include <iostream>

namespace sml {

	struct mat4
	{
		float values[4][4];

		// Matrix operations
		vec4 MultiplyVec(mat4* mat, vec4* vec);
		mat4 MultiplyMat(mat4* mat1, mat4* mat2);

		// Matrix utility functions
		static void MakeNull(struct mat4* mat);
		static void MakeIdentity(struct mat4* mat);
		static void PrintElements(struct mat4* mat);

		// Matrix types
		static mat4 CreateRotationMatrix(float angleInDegrees, struct vec3 axis);
		static mat4 CreateTranslationMatrix(float x, float y, float z);
		static mat4 CreateScaleMatrix(float xScale, float yScale, float zScale);

		static mat4 CreateLookAtMatrix(const vec3& cameraPosition, const vec3& cameraDirection, const vec3& up);

		static mat4 CreateOrthographic(float left, float right, float top, float bottom, float zNear, float zFar);
		static mat4 CreatePerspective(float left, float right, float top, float bottom, float zNear, float zFar);
		static mat4 CreatePerspective(float fov, float aspectRatio, float zNear, float zFar);

		// Overloaded operators
		float* operator[](int index);
		mat4 operator*(mat4 another);
		vec4 operator*(vec4 vec);

		// Other Utility Functions
		static mat4 CreateNDCToViewportMatrix(float width, float height);
	};

	std::ostream& operator<<(std::ostream & stream, mat4 matrix);
}

