#include "Plane.h"
#include "BoxBounds.h"

namespace JustEngine
{
	Plane::Plane(Vector3& normal, Vector3& position)
	{
		SetNormalAndPosition(normal, position);
	}

	Plane::Plane(): mDistance(0), mNormal()
	{

	}

	void Plane::SetNormalAndPosition(Vector3 & normal, Vector3 & position)
	{
		mNormal = normal.Normalized();
		mDistance = normal*position;
	}

	Side Plane::IsInside(Vector3& position) const
	{
		float d = GetDistance(position);
		if (d > 0) return Side::In;
		if (d < 0) return Side::Out;
		return Side::Cross;
	}

	Side Plane::IsInside(const BoxBounds& aabb) const
	{
		if (GetDistance(aabb.GetVertexP(mNormal)) < 0) {
			return Side::Out;
		}
		if (GetDistance(aabb.GetVertexN(mNormal)) > 0)
		{
			return Side::In;
		}
		return Side::Cross;
	}

	float Plane::GetDistance(Vector3& point) const
	{
		return mNormal.x * point.x + mNormal.y * point.y + mNormal.z * point.z + mDistance;
	}

	float Plane::GetDistance() const
	{
		return mDistance;
	}

	Vector3 Plane::GetNormal() const
	{
		return mNormal;
	}

}
