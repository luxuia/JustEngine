#include <cstring>

#include "Quaternion.h"

namespace JustEngine
{
	Quaternion::Quaternion()
	{
		a = b = c = d = 0;
	}

	Quaternion::Quaternion(float x, float y, float z, float w): a(x),b(y),c(z),d(w)
	{
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
	bool Quaternion::operator==(const Quaternion & other)
	{
		return a == other.a && b == other.b && c == other.c && d == other.d;
	}
	bool Quaternion::operator!=(const Quaternion & other)
	{
		return !(*this == other);
	}
	Quaternion & Quaternion::operator=(const Quaternion & other)
	{
		memcpy(&a, &other, sizeof(float) * 4);
		return *this;
	}
}
