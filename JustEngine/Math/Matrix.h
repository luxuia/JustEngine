#pragma once

#include "../Macros.h"

namespace JustEngine
{
	class Vector3;
	class Quaternion;

	class DLL_EXPORT Matrix4
	{
	public:
		
		const static Matrix4 identity;

		union
		{
			float r[16];
			unsigned int u[16];
			float m[4][4];
		};

		Matrix4();
		Matrix4( const float* data );
		Matrix4( const Matrix4& data );
		Matrix4(float);

		Matrix4& Identity();

		Matrix4& RotateY(float radian);

		static Matrix4 Rotate(Quaternion& quat);
		static Matrix4 Transform(Vector3& pos);
		static Matrix4 Scale(Vector3& scale);

		static Matrix4 CreateRotateY(float radian);

		Matrix4 Transpose() const;

		Matrix4 Invert() const;

		Matrix4 operator *(const Matrix4& data);

		Matrix4& LookAt( const Vector3& eye, const Vector3& at, const Vector3& up );

		Matrix4& PerspectiveFovLH(float fov, float aspect, float near, float far);

		// this function interface maybe useless? >.<
		Matrix4& PerspectiveLH( float width, float height, float near, float far );

		Matrix4& OrthoLH( float width, float height, float neawr, float far );
	};
}