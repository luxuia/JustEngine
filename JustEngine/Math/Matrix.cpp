
#include "Matrix.h"
#include <string>
#include <cmath>
#include "Vector.h"

namespace Math
{
	Matrix4::Matrix4()
	{
		memset(r, 0, 16 * sizeof(float));
	}

	Matrix4::Matrix4( const float* data )
	{
		memcpy( r, data, 16*sizeof(float ));
	}

	Matrix4::Matrix4( const Matrix4& data )
	{
		memcpy( r, data.r, 16 * sizeof(float) );
	}

	Matrix4::Matrix4(float v)
	{
		memset(r, 0, 16 * sizeof(float));
		r[0] = r[5] = r[10] = r[15] = v;
	}

	Matrix4& Matrix4::Identity()
	{
		memset( r, 0, 16 *sizeof(float));
		r[0] = 1.0f; r[5] = 1.0f; r[10] = 1.0f; r[15] = 1.0f;

		return *this;
	}

	Matrix4 & Matrix4::RotateY(float radian)
	{
		return *this * Matrix4::CreateRotateY(radian);
	}

	Matrix4 Matrix4::CreateRotateY(float radian)
	{
		Matrix4 res = Matrix4().Identity();
		float cosr = cos(radian);
		float sinr = sin(radian);

		res.m[0][0] = cosr; res.m[0][2] = -sinr;
		res.m[2][0] = sinr; res.m[2][2] = cosr;

		return res;
	}

	Matrix4 Matrix4::Invert() const
	{
		Matrix4 M;

		float det = r[0] * (r[5] * r[10] - r[6] * r[9])
			+ r[1] * (r[6] * r[8] - r[4] * r[10])
			+ r[2] * (r[4] * r[9] - r[5] * r[8]);
		if (det != 0)
		{
			float det2 = 1.0f / det;
			M.r[0] = (r[5] * r[10] - r[6] * r[9]) * det2;
			M.r[1] = (r[2] * r[9] - r[1] * r[10]) * det2;
			M.r[2] = (r[1] * r[6] - r[2] * r[5]) * det2;
			M.r[3] = 0.0f;
			M.r[4] = (r[6] * r[8] - r[4] * r[10]) * det2;
			M.r[5] = (r[0] * r[10] - r[2] * r[8]) * det2;
			M.r[6] = (r[2] * r[4] - r[0] * r[6]) * det2;
			M.r[7] = 0.0f;
			M.r[8] = (r[4] * r[9] - r[5] * r[8]) * det2;
			M.r[9] = (r[1] * r[8] - r[0] * r[9]) * det2;
			M.r[10] = (r[0] * r[5] - r[1] * r[4]) * det2;
			M.r[11] = 0.0f;
			M.r[12] = -(r[12] * M.r[0] + r[13] * M.r[4] + r[14] * M.r[8]);
			M.r[13] = -(r[12] * M.r[1] + r[13] * M.r[5] + r[14] * M.r[9]);
			M.r[14] = -(r[12] * M.r[2] + r[13] * M.r[6] + r[14] * M.r[10]);
			M.r[15] = 1.0f;
		}

		return M;
	}

	Matrix4 Matrix4::Transpose( ) const
	{
		const float data[] = {
			r[0], r[4], r[8], r[12],
			r[1], r[5], r[9], r[13],
			r[2], r[6], r[10], r[14],
			r[3], r[7], r[11], r[15]
		};

		return Matrix4( data );
	}

	Matrix4& Matrix4::operator*(const Matrix4& data)
	{
		Matrix4 M;

		M.r[0] = r[0] * data.r[0] + r[4] * data.r[1] + r[8] * data.r[2];
		M.r[1] = r[1] * data.r[0] + r[5] * data.r[1] + r[9] * data.r[2];
		M.r[2] = r[2] * data.r[0] + r[6] * data.r[1] + r[10] * data.r[2];
		M.r[3] = 0.0f;
		M.r[4] = r[0] * data.r[4] + r[4] * data.r[5] + r[8] * data.r[6];
		M.r[5] = r[1] * data.r[4] + r[5] * data.r[5] + r[9] * data.r[6];
		M.r[6] = r[2] * data.r[4] + r[6] * data.r[5] + r[10] * data.r[6];
		M.r[7] = 0.0f;
		M.r[8] = r[0] * data.r[8] + r[4] * data.r[9] + r[8] * data.r[10];
		M.r[9] = r[1] * data.r[8] + r[5] * data.r[9] + r[9] * data.r[10];
		M.r[10] = r[2] * data.r[8] + r[6] * data.r[9] + r[10] * data.r[10];
		M.r[11] = 0.0f;
		M.r[12] = r[0] * data.r[12] + r[4] * data.r[13] + r[8] * data.r[14] + r[12];
		M.r[13] = r[1] * data.r[12] + r[5] * data.r[13] + r[9] * data.r[14] + r[13];
		M.r[14] = r[2] * data.r[12] + r[6] * data.r[13] + r[10] * data.r[14] + r[14];
		M.r[15] = 1.0f;

		return M;
	}

	Matrix4 & Math::Matrix4::LookAt(const Vector3 & eye, const Vector3 & at, const Vector3 & up)
	{
		Vector3 z = (at - eye).Normalized();
		
		Vector3 x = up.CrossProduct( z );

		Vector3 y = z.CrossProduct( x );

		m[0][0] = x.x;
		m[1][0] = x.y;
		m[2][0] = x.z;
		m[3][0] = -eye*x;

		m[0][1] = y.x;
		m[1][1] = y.y;
		m[2][1] = y.z;
		m[3][1] = -eye*y;

		m[0][2] = z.x;
		m[1][2] = z.y;
		m[2][2] = z.z;
		m[3][2] = -eye*z;

		m[3][3] = 1.f;

		return *this;
	}

	Matrix4& Matrix4::PerspectiveFovLH(float fov, float aspect, float near, float far)
	{
		float ctanFov = atan(fov);
		float width = ctanFov / aspect;

		float fRange = far / (far - near);

		m[0][0] = width;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = ctanFov;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = fRange;
		m[2][3] = 1.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = -fRange * near;
		m[3][3] = 0.0f;

		return *this;
	}


	Matrix4& Matrix4::PerspectiveLH( float width, float height, float near, float far )
	{
		float nearz2, fRange;

		nearz2 = near + near;
		fRange = far / (far - near);

		m[0][0] = nearz2 / width;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = nearz2 / height;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = fRange;
		m[2][3] = 1.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = -fRange * near;
		m[3][3] = 0.0f;

		return *this;
	}

	Matrix4& Matrix4::OrthoLH( float width, float height, float near, float far )
	{
		float fRange = 1.f / (far - near);

		m[0][0] = 2.f / width;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = 2.f / height;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = fRange;
		m[2][3] = 0.f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = -fRange * near;
		m[3][3] = 1.f;

		return *this;
	}

	const Matrix4 Matrix4::identity = { 1 };
}
