#pragma once

#include "../Macros.h"
#include "Vector.h"

namespace Math
{
	class DLL_EXPORT Matrix4
	{
	public:
		union
		{
			float r[16];
			unsigned int u[16];
			float m[4][4];
		};

		Matrix4();
		Matrix4( const float* data );
		Matrix4( const Matrix4& data );

		void Identity();

		Matrix4 Transpose() const;

		Matrix4 Invert() const;

		Matrix4& operator *(const Matrix4& data);

		Matrix4& LookAt( Vector3 eye, Vector3 at, Vector3 up );

		Matrix4& PerspectiveLH( float width, float height, float near, float far );

		Matrix4& OrthoLH( float width, float height, float neawr, float far );

		
	};
}