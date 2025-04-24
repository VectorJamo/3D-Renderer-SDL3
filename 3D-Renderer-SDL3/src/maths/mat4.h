#pragma once

#include "vec4.h"
#include "vec3.h"

#include <iostream>

namespace sml {

	struct mat4
	{
		float values[4][4];
	private:
		// Matrix operations
		static vec4 MultiplyVec(const mat4& mat, const vec4& vec);
		static mat4 MultiplyMat(const mat4& mat1, const mat4& mat2);

	public:
		// Matrix utility functions
		static void MakeNull(struct mat4* mat);
		static void MakeIdentity(mat4* mat);
		static void PrintElements(mat4* mat);

		// Matrix types
		static mat4 CreateRotationMatrix(float angle, vec3 axis);
		static mat4 CreateTranslationMatrix(float x, float y, float z);
		static mat4 CreateScaleMatrix(float xScale, float yScale, float zScale);

		static mat4 CreateLookAtMatrix(const vec3& cameraPosition, const vec3& cameraTarget, const vec3& up);
		
		static mat4 CreateOrthographic(float left, float right, float top, float bottom, float zNear, float zFar);
		/**
		 * Might not provide expected results. Use the perspective projection matrix with hFov instead.
		 */
		static mat4 CreatePerspective(float left, float right, float top, float bottom, float zNear, float zFar);
		static mat4 CreatePerspective(float hFov, float aspectRatio, float zNear, float zFar);

		static mat4 CreateNDCToViewportMatrix(float width, float height);

		// Overloaded operators
		float* operator[](int index);
		mat4 operator*(mat4 another);
		vec4 operator*(vec4 vec);
	};

	std::ostream& operator<<(std::ostream & stream, mat4 matrix);
}

