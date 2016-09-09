#pragma once

#include <array>

#include "pch.h"
#include "Collidable.h"
#include "Plane.h"

namespace JustEngine
{
	class BoxBounds;

	class DLL_EXPORT Frustum : public Collidable
	{
	protected:
		std::array<Plane, 6> mPLanes;

	public:
		void Setup(float fov, float aspect, float nearplane, float farplane);

		virtual Side IsInside(Vector3& position) const;

		virtual Side IsInside(const BoxBounds& aabb) const;

		void Transform(const Matrix4& matrix);

		void Update();
	};
}