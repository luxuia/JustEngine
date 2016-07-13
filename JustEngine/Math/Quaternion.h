#pragma once

#include "../Macros.h"
#include "Vector.h"

namespace Math
{
	class DLL_EXPORT Quaternion
	{
	public:
		union
		{
			// rotate align (x, y, z) theta 
			struct { float a, b, c, d; };// = (x, y, z) * sin(theta/2), cos(theta/2)
			struct { Vector3 u; float v; };
		};
		
		Quaternion();

		Quaternion(Vector3 u, float v);

		Vector3 operator*(const Vector3 other);

		Quaternion operator* (const Quaternion other);
	};

}