#include "Quaternion.h"

namespace Math
{
	Quaternion::Quaternion()
	{
		a = b = c = d = 0;
	}

	Quaternion::Quaternion(Vector3 iu, float iv)
	{
		u = iu;
		v = iv;
	}

	Vector3 Quaternion::operator*(const Vector3 other)
	{
		Quaternion q = { u.CrossProduct(other) + other*v, -u*other };
		return (q*GetConjudget()).u;
	}

	Quaternion Quaternion::GetConjudget() const
	{
		return{ -u, v };
	}

	Quaternion Quaternion::operator*(const Quaternion other)
	{
		return { u.CrossProduct(other.u) + other.u*v + u*other.v , v*other.v - u*other.u };
	}
}
