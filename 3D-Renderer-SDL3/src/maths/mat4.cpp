#include "mat4.h"
#include <cmath>

#define PI 3.1415f

namespace sml {
	vec4 mat4::MultiplyVec(const mat4& mat, const vec4& vec)
	{
		vec4 transformedVec;
		transformedVec.x = (mat.values[0][0] * vec.x + mat.values[0][1] * vec.y + mat.values[0][2] * vec.z + mat.values[0][3] * vec.w);
		transformedVec.y = (mat.values[1][0] * vec.x + mat.values[1][1] * vec.y + mat.values[1][2] * vec.z + mat.values[1][3] * vec.w);
		transformedVec.z = (mat.values[2][0] * vec.x + mat.values[2][1] * vec.y + mat.values[2][2] * vec.z + mat.values[2][3] * vec.w);
		transformedVec.w = (mat.values[3][0] * vec.x + mat.values[3][1] * vec.y + mat.values[3][2] * vec.z + mat.values[3][3] * vec.w);

		return transformedVec;
	}

	mat4 mat4::MultiplyMat(const mat4& mat1, const mat4& mat2)
	{
		mat4 newMat;
		MakeIdentity(&newMat);

		int i;
		for (i = 0; i < 4; i++)
		{
			newMat.values[i][0] = mat1.values[i][0] * mat2.values[0][0] + mat1.values[i][1] * mat2.values[1][0] + mat1.values[i][2] * mat2.values[2][0] + mat1.values[i][3] * mat2.values[3][0];
			newMat.values[i][1] = mat1.values[i][0] * mat2.values[0][1] + mat1.values[i][1] * mat2.values[1][1] + mat1.values[i][2] * mat2.values[2][1] + mat1.values[i][3] * mat2.values[3][1];
			newMat.values[i][2] = mat1.values[i][0] * mat2.values[0][2] + mat1.values[i][1] * mat2.values[1][2] + mat1.values[i][2] * mat2.values[2][2] + mat1.values[i][3] * mat2.values[3][2];
			newMat.values[i][3] = mat1.values[i][0] * mat2.values[0][3] + mat1.values[i][1] * mat2.values[1][3] + mat1.values[i][2] * mat2.values[2][3] + mat1.values[i][3] * mat2.values[3][3];
		}
		return newMat;
	}

	void mat4::MakeNull(mat4* mat)
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

	void mat4::MakeIdentity(mat4* mat)
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

	void mat4::PrintElements(mat4* mat)
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
	mat4 mat4::CreateRotationMatrix(float angle, vec3 axis)
	{
		mat4 rotationMatrix;
		MakeIdentity(&rotationMatrix);

		float angleInRadians = angle * (PI / 180.0f);

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
	mat4 mat4::CreateLookAtMatrix(const vec3& cameraPosition, const vec3& cameraTarget, const vec3& up)
	{
		mat4 lookAt;
		MakeIdentity(&lookAt);

		// Create the view coordinate space
		// The view space's basis vectors
		vec3 viewBasisZ = cameraTarget - cameraPosition;
		viewBasisZ = viewBasisZ.GetNormalized() * -1; // Camera(view) space's +ve Z basis
		vec3 viewBasisX = vec3::CrossProduct(up, viewBasisZ).GetNormalized();
		vec3 viewBasisY = vec3::CrossProduct(viewBasisZ, viewBasisX);

		mat4 translation = mat4::CreateTranslationMatrix(-cameraPosition.x, -cameraPosition.y, -cameraPosition.z); // Inverse of the translation matrix to the camera (Reverse transformation from camera to world space)

		// Inverse of the matrix that maps the world's basis vectors to the camera's basis vector (Reverse transformation from camera to world space)
		lookAt[0][0] = viewBasisX.x;
		lookAt[0][1] = viewBasisX.y;
		lookAt[0][2] = viewBasisX.z;

		lookAt[1][0] = viewBasisY.x;
		lookAt[1][1] = viewBasisY.y;
		lookAt[1][2] = viewBasisY.z;

		lookAt[2][0] = viewBasisZ.x;
		lookAt[2][1] = viewBasisZ.y;
		lookAt[2][2] = viewBasisZ.z;

		return lookAt * translation;
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
	mat4 mat4::CreatePerspective(float hFov, float aspectRatio, float zNear, float zFar)
	{
		// Not particularly efficient but great for learning and understanding how perspective projection works.
		mat4 perspective;
		MakeIdentity(&perspective);

		perspective.values[0][0] = zNear;
		perspective.values[1][1] = zNear;
		perspective.values[2][2] = zNear + zFar;
		perspective.values[2][3] = -(zNear * zFar);
		perspective.values[3][2] = 1.0f;
		
		float hFovRadians = hFov * (PI / 180.0f);

		// Near plane dimensions
		float width = 2 * tan(hFovRadians / 2) * (-1 * zNear);
		float left = -(width / 2);
		float right = width / 2;
		float height = width / aspectRatio;
		float top = height / 2;
		float bottom = -(height / 2); 

		mat4 ortho = CreateOrthographic(left, right, top, bottom, zNear, zFar);

		mat4 perspectiveProjection = ortho * perspective;

		return perspectiveProjection;
	}
	float* mat4::operator[](int index)
	{
		return values[index];
	}
	mat4 mat4::operator*(mat4 another)
	{
		mat4 result = MultiplyMat(*this, another);
		return result;
	}
	vec4 mat4::operator*(vec4 vec)
	{
		vec4 result = MultiplyVec(*this, vec);
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
		sml::mat4::PrintElements(&matrix);
		return stream;
	}
}

