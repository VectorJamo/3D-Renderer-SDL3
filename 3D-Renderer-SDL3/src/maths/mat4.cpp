#include "mat4.h"
#include <math.h>

#define PI 3.1415f

namespace sml {
	vec4 mat4::MultiplyVec(mat4* mat, vec4* vec)
	{
		vec4 transformedVec;
		transformedVec.x = (mat->values[0][0] * vec->x + mat->values[0][1] * vec->y + mat->values[0][2] * vec->z + mat->values[0][3] * vec->w);
		transformedVec.y = (mat->values[1][0] * vec->x + mat->values[1][1] * vec->y + mat->values[1][2] * vec->z + mat->values[1][3] * vec->w);
		transformedVec.z = (mat->values[2][0] * vec->x + mat->values[2][1] * vec->y + mat->values[2][2] * vec->z + mat->values[2][3] * vec->w);
		transformedVec.w = (mat->values[3][0] * vec->x + mat->values[3][1] * vec->y + mat->values[3][2] * vec->z + mat->values[3][3] * vec->w);

		return transformedVec;
	}

	mat4 mat4::MultiplyMat(mat4* mat1, mat4* mat2)
	{
		mat4 newMat;
		MakeIdentity(&newMat);

		int i;
		for (i = 0; i < 4; i++)
		{
			newMat.values[i][0] = mat1->values[i][0] * mat2->values[0][0] + mat1->values[i][1] * mat2->values[1][0] + mat1->values[i][2] * mat2->values[2][0] + mat1->values[i][3] * mat2->values[3][0];
			newMat.values[i][1] = mat1->values[i][0] * mat2->values[0][1] + mat1->values[i][1] * mat2->values[1][1] + mat1->values[i][2] * mat2->values[2][1] + mat1->values[i][3] * mat2->values[3][1];
			newMat.values[i][2] = mat1->values[i][0] * mat2->values[0][2] + mat1->values[i][1] * mat2->values[1][2] + mat1->values[i][2] * mat2->values[2][2] + mat1->values[i][3] * mat2->values[3][2];
			newMat.values[i][3] = mat1->values[i][0] * mat2->values[0][3] + mat1->values[i][1] * mat2->values[1][3] + mat1->values[i][2] * mat2->values[2][3] + mat1->values[i][3] * mat2->values[3][3];
		}
		return newMat;
	}

	void mat4::MakeNull(struct mat4* mat)
	{
		int row, col;
		for (row = 0; row < 4; row++)
		{
			for (col = 0; col < 4; col++)
			{
				mat->values[row][col] = 0.0f; // Set all the values to be 0
			}
		}
	}

	void mat4::MakeIdentity(struct mat4* mat)
	{
		int row, col;
		for (row = 0; row < 4; row++)
		{
			for (col = 0; col < 4; col++)
			{
				if (row == col)
				{
					mat->values[row][col] = 1.0f;

				}
				else {
					mat->values[row][col] = 0.0f; // Set all the values to be 0
				}
			}
		}
	}

	void mat4::PrintElements(struct mat4* mat)
	{
		int row, col;
		for (row = 0; row < 4; row++)
		{
			printf("[");
			for (col = 0; col < 4; col++)
			{
				printf(col == 3 ? "%f] \n" : "%f ", mat->values[row][col]);
			}
		}
	}
	mat4 mat4::CreateRotationMatrix(float angleInDegrees, vec3 axis)
	{
		mat4 rotationMatrix;
		MakeIdentity(&rotationMatrix);

		float angleInRadians = angleInDegrees * (PI / 180.0f);

		if (axis.x)
		{
			rotationMatrix.values[1][1] = cos(angleInRadians);
			rotationMatrix.values[1][2] = -sin(angleInRadians);
			rotationMatrix.values[2][1] = sin(angleInRadians);
			rotationMatrix.values[2][2] = cos(angleInRadians);
		}
		else if (axis.y)
		{
			rotationMatrix.values[0][0] = cos(angleInRadians);
			rotationMatrix.values[0][2] = sin(angleInRadians);
			rotationMatrix.values[2][0] = -sin(angleInRadians);
			rotationMatrix.values[2][2] = cos(angleInRadians);
		}
		else if (axis.z)
		{
			rotationMatrix.values[0][0] = cos(angleInRadians);
			rotationMatrix.values[0][1] = -sin(angleInRadians);
			rotationMatrix.values[1][0] = sin(angleInRadians);
			rotationMatrix.values[1][1] = cos(angleInRadians);
		}

		return rotationMatrix;
	}
	mat4 mat4::CreateTranslationMatrix(float x, float y, float z)
	{
		mat4 translationMatrix;
		MakeIdentity(&translationMatrix);

		translationMatrix.values[0][3] = x;
		translationMatrix.values[1][3] = y;
		translationMatrix.values[2][3] = z;

		return translationMatrix;
	}
	mat4 mat4::CreateScaleMatrix(float xScale, float yScale, float zScale)
	{
		mat4 scale;
		MakeIdentity(&scale);

		scale.values[0][0] = xScale;
		scale.values[1][1] = yScale;
		scale.values[2][2] = zScale;

		return scale;
	}
	mat4 mat4::CreateLookAtMatrix(const vec3& cameraPosition, const vec3& cameraDirection, const vec3& up)
	{
		return mat4();
	}
	mat4 mat4::CreateOrthographic(float left, float right, float top, float bottom, float zNear, float zFar)
	{
		mat4 orthographic;
		MakeIdentity(&orthographic);

		orthographic.values[0][0] = 2 / (right - left);
		orthographic.values[1][1] = 2 / (top - bottom);
		orthographic.values[2][2] = 2 / (zFar - zNear);
		orthographic.values[2][3] = -((zFar + zNear) / (zFar - zNear));

		return orthographic;
	}
	mat4 mat4::CreatePerspective(float left, float right, float top, float bottom, float zNear, float zFar)
	{
		mat4 perspective;
		MakeIdentity(&perspective);

		perspective.values[0][0] = zNear;
		perspective.values[1][1] = zNear;
		perspective.values[2][2] = zNear + zFar;
		perspective.values[2][3] = -(zNear * zFar);
		perspective.values[3][2] = 1.0f;

		mat4 ortho = CreateOrthographic(left, right, top, bottom, zNear, zFar);

		mat4 perspectiveProjection = ortho * perspective;

		return perspectiveProjection; 
	}
	mat4 mat4::CreatePerspective(float fov, float aspectRatio, float zNear, float zFar)
	{
		return mat4();
	}
	float* mat4::operator[](int index)
	{
		return values[index];
	}
	mat4 mat4::operator*(mat4 another)
	{
		mat4 result = MultiplyMat(this, &another);
		return result;
	}
	vec4 mat4::operator*(vec4 vec)
	{
		vec4 result = MultiplyVec(this, &vec);
		return result;
	}

	mat4 mat4::CreateNDCToViewportMatrix(float width, float height)
	{
		mat4 ndcToViewportMatrix;
		MakeIdentity(&ndcToViewportMatrix);
		// The X-basis vector remains the same but is scaled by width/2.
		// The Y-basis vector is flipped and scaled by height/2.
		// The space is translated by width/2 to the right and height/2 to down.
		
		ndcToViewportMatrix[0][0] = width/2;
		ndcToViewportMatrix[1][1] = -height/2;
		ndcToViewportMatrix[0][3] = width/2;
		ndcToViewportMatrix[1][3] = height/2;

		return ndcToViewportMatrix;
	}

	std::ostream& operator<<(std::ostream& stream, mat4 matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			stream << " ";
			for (int j = 0; j < 4; j++)
			{
				stream << matrix[i][j];
				stream << " ";
			}
			stream << "\n";
		}
		return stream;
	}
}

