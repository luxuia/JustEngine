#include "BoxBounds.h"

namespace JustEngine
{
	BoxBounds::BoxBounds(Vector3 min, Vector3 max):mMin(min),mMax(max)
	{
		mSize = max - min;
		mExtents = (max - min) * 0.5f;
		mCenter = mExtents + min;

		mDirty = false;
	}
	void BoxBounds::SetMinMax(Vector3 min, Vector3 max)
	{
		mMin = min;
		mMax = max;

		mSize = max - min;
		mExtents = (max - min) * 0.5f;
		mCenter = mExtents + min;
		
		mDirty = false;
	}
	Side BoxBounds::IsInside(const Vector3 & point) const
	{
		if (point.x > mMax.x || point.y > mMax.y || point.z > mMax.z 
			|| point.x < mMin.x || point.y < mMin.y || point.z < mMin.z)
		{
			return Side::Out;
		}
		return Side::In;
	}
	Side BoxBounds::IsInSide(const BoxBounds & aabb) const
	{
		const Vector3 max = aabb.GetMax();
		const Vector3 min = aabb.GetMin();

		if (min > mMin && max < mMax)
		{
			return Side::In;
		}
		else if (max >= mMin && min <= mMax)
		{
			return Side::Cross;
		}
		else
		{
			return Side::Out;
		}
	}

	Vector3	BoxBounds::GetMin() const
	{
		return mMin;
	}
	Vector3 BoxBounds::GetMax() const
	{
		return mMax;
	}
	Vector3 BoxBounds::GetCenter() const
	{
		return mCenter;
	}
	Vector3 BoxBounds::GetExtents() const
	{
		return mExtents;
	}
	Vector3 BoxBounds::GetSize() const
	{
		return mSize;
	}

	Vector3 BoxBounds::GetVertexP(Vector3 normal) const
	{
		return Vector3(
			normal.x > 0 ? mMax.x : mMin.x,
			normal.y > 0 ? mMax.y : mMin.y,
			normal.z > 0 ? mMax.z : mMin.z
		);
	}

	Vector3 BoxBounds::GetVertexN(Vector3 normal) const
	{
		return Vector3(
			normal.x < 0 ? mMax.x : mMin.x,
			normal.y < 0 ? mMax.y : mMin.y,
			normal.z < 0 ? mMax.z : mMin.z
		);
	}

}
