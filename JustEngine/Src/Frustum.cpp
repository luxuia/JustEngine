#include "Frustum.h"

namespace JustEngine
{
	void Frustum::Setup(float fov, float aspect, float nearplane, float farplane)
	{

	}

	Side Frustum::IsInside(Vector3 & position) const
	{
		return Side();
	}

	Side Frustum::IsInside(const BoxBounds & aabb) const
	{
		return Side();
	}

	void Frustum::Transform(const Matrix4& matrix)
	{
		Matrix4 trans = matrix.Transpose();
		Vector3* right = (Vector3*)trans.m[0];
		Vector3* up = (Vector3*)trans.m[1];
		Vector3* forward = (Vector3*)trans.m[2];

	}

	void Frustum::Update()
	{
	}

}