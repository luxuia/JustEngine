#pragma once

#include <cmath>

#include "Quaternion.h"
#include "Vector.h"

namespace JustEngine
{
	class DLL_EXPORT MathUtil
	{
	public:
		static const float PI;
		static const float HalfPI;
		static const float DegToRad;
		static const float RadToDeg;

		static Quaternion AxisRadToQuat(const Vector3& axis, float rad);
		static Quaternion AxisRadToQuat(float x, float y, float z, float rad);

		static Quaternion EulerRadToQuat(const Vector3& eulerRad);
		static Quaternion EulerRadToQuat(float yaw, float pitch, float roll);
	};
}