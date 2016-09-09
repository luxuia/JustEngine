#pragma once

#include "pch.h"

namespace JustEngine
{
	class BoxBounds;

	class DLL_EXPORT Collidable
	{
	public :
		// is point inside Collidable
		virtual Side IsInside(Vector3& point) const = 0;
		// is aabb box in Collidable
		virtual Side IsInside(const BoxBounds& aabb) const = 0;
	};
}
