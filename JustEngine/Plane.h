#pragma once

#include "pch.h"

namespace JustEngine
{
	class BoxBounds;

	class DLL_EXPORT Plane
	{
	protected:
		Vector3 mNormal;
		float mDistance;
	public:
		Plane();
		Plane(Vector3& normal, Vector3& position);

		void SetNormalAndPosition(Vector3& normal, Vector3& position);

		Side IsInside(Vector3& position) const;
		Side IsInside(const BoxBounds& aabb) const;

		float GetDistance(Vector3& point) const;
		Vector3 GetNormal() const;
		float GetDistance() const;
	};
}