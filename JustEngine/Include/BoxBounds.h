#pragma once

#include "pch.h"
#include "Collidable.h"

namespace JustEngine
{
	class DLL_EXPORT BoxBounds : public Collidable {
	protected:
		Vector3 mMin, mMax;

		Vector3 mExtents, mSize;

		Vector3 mCenter;

		bool mInfinite = false;
		bool mDirty = false;

	public:
		BoxBounds(Vector3 min, Vector3 max);

		void SetMinMax(Vector3 min, Vector3 max);

		virtual Side IsInside(const Vector3& point) const;

		virtual Side IsInSide(const BoxBounds& aabb) const;

		Vector3 GetMin() const;

		Vector3 GetMax() const;

		Vector3 GetCenter() const;

		Vector3 GetExtents() const;

		Vector3 GetSize() const;

		Vector3 GetVertexP(Vector3 normal) const;
		Vector3 GetVertexN(Vector3 normal) const;
	};
}
