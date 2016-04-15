#include "Vector.h"
#include <cmath>

namespace Math
{
	using namespace std;

	void Vector4::Absolute()
	{
		x = abs( x );
		y = abs( y );
		z = abs( z );
		w = 1.f;
	}

	void Vector4::Zero()
	{
		x = y = z = w = 0.0f;
	}

	void Vector4::Normalize()
	{
		float mag = x * x + y * y + z * z;
		if (mag > 0.0f)
		{
			float a = 1.0f / sqrt( mag );
			x *= a; y *= a; z *= a;
		}
		w = 1.0f;
	}

	Vector4 Vector4::Normalized() const
	{
		Vector4 vector( *this );
		vector.Normalize();
		return vector;
	}

	float Vector4::Length() const
	{
		return sqrt( x * x + y * y + z * z );
	}

	float Vector4::SquareLength() const
	{
		return x * x + y * y + z * z;
	}

	float Vector4::Distance( Vector4 other ) const
	{
		float dx = x - other.x;
		float dy = y - other.y;
		float dz = z - other.z;
		return sqrt( dx * dx + dy * dy + dz * dz );
	}

	Vector4 Vector4::CrossProduct( Vector4 other ) const
	{
		return Vector4(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x,
			1.0f
			);
	}

	Vector4 Vector4::Project( Vector4 other ) const
	{
		return other * (*this * other / other.SquareLength());
	}

	Vector4 Vector4::Clone() const
	{
		return Vector4( *this );
	}

	bool Vector4::operator == (Vector4 other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector4::operator != (Vector4 other) const
	{
		return x != other.x || y != other.y || z != other.z;
	}

	bool Vector4::operator < (Vector4 other) const
	{
		return x < other.x && y < other.y && z < other.z;
	}

	bool Vector4::operator <= (Vector4 other) const
	{
		return x <= other.x && y <= other.y && z <= other.z;
	}

	bool Vector4::operator >( Vector4 other ) const
	{
		return x > other.x && y > other.y && z > other.z;
	}

	bool Vector4::operator >= (Vector4 other) const
	{
		return x >= other.x && y >= other.y && z >= other.z;
	}

	Vector4 &Vector4::operator = (Vector4 other)
	{
		x = other.x; y = other.y; z = other.z;
		return *this;
	}

	Vector4 Vector4::operator - () const
	{
		return Vector4( -x, -y, -z, 1.0f );
	}

	Vector4 Vector4::operator + (Vector4 other) const
	{
		return Vector4( x + other.x, y + other.y, z + other.z, 1.0f );
	}

	Vector4 Vector4::operator - (Vector4 other) const
	{
		return Vector4( x - other.x, y - other.y, z - other.z, 1.0f );
	}

	float Vector4::operator * (Vector4 other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	Vector4 Vector4::operator * (const float other) const
	{
		return Vector4( x * other, y * other, z * other, 1.0f );
	}

	Vector4 Vector4::operator / (const float other) const
	{
		float i = 1.0f / other;
		return Vector4( x * i, y * i, z * i, 1.0f );
	}



	void Vector3::Absolute()
	{
		x = abs( x );
		y = abs( y );
		z = abs( z );
	}

	void Vector3::Zero()
	{
		x = y = z = 0.0f;
	}

	void Vector3::Normalize()
	{
		float mag = x * x + y * y + z * z;
		if (mag > 0.0f)
		{
			float a = 1.0f / sqrt( mag );
			x *= a; y *= a; z *= a;
		}
	}

	Vector3 Vector3::Normalized() const
	{
		Vector3 vector( *this );
		vector.Normalize();
		return vector;
	}

	float Vector3::Length() const
	{
		return sqrt( x * x + y * y + z * z );
	}

	float Vector3::SquareLength() const
	{
		return x * x + y * y + z * z;
	}

	float Vector3::Distance( Vector3 other ) const
	{
		float dx = x - other.x;
		float dy = y - other.y;
		float dz = z - other.z;
		return sqrt( dx * dx + dy * dy + dz * dz );
	}

	Vector3 Vector3::CrossProduct( Vector3 other ) const
	{
		return Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
			);
	}

	Vector3 Vector3::Project( Vector3 other ) const
	{
		return other * (*this * other / other.SquareLength());
	}

	Vector3 Vector3::Clone() const
	{
		return Vector3( *this );
	}

	bool Vector3::operator == (Vector3 other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector3::operator != (Vector3 other) const
	{
		return x != other.x || y != other.y || z != other.z;
	}

	bool Vector3::operator < (Vector3 other) const
	{
		return x < other.x && y < other.y && z < other.z;
	}

	bool Vector3::operator <= (Vector3 other) const
	{
		return x <= other.x && y <= other.y && z <= other.z;
	}

	bool Vector3::operator >( Vector3 other ) const
	{
		return x > other.x && y > other.y && z > other.z;
	}

	bool Vector3::operator >= (Vector3 other) const
	{
		return x >= other.x && y >= other.y && z >= other.z;
	}

	Vector3 &Vector3::operator = (Vector3 other)
	{
		x = other.x; y = other.y; z = other.z;
		return *this;
	}

	Vector3 Vector3::operator - () const
	{
		return Vector3( -x, -y, -z);
	}

	Vector3 Vector3::operator + (Vector3 other) const
	{
		return Vector3( x + other.x, y + other.y, z + other.z);
	}

	Vector3 Vector3::operator - (Vector3 other) const
	{
		return Vector3( x - other.x, y - other.y, z - other.z);
	}

	float Vector3::operator * (Vector3 other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	Vector3 Vector3::operator * (const float other) const
	{
		return Vector3( x * other, y * other, z * other);
	}

	Vector3 Vector3::operator / (const float other) const
	{
		float i = 1.0f / other;
		return Vector3( x * i, y * i, z * i);
	}
}