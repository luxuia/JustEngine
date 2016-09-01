#include "MathUtil.h"

namespace JustEngine
{
	const float MathUtil::PI = 3.1415926535897932384626433832795028841971693993751f;

	const float MathUtil::HalfPI = 1.5707963267948966192313216916397514420985846996875f;

	// PI / 180
	const float MathUtil::DegToRad = 0.017453292519943295769236907684886127134428718885417f;

	// 180 / PI
	const float MathUtil::RadToDeg = 57.295779513082320876798154814105170332405472466565f;


	Quaternion MathUtil::AxisRadToQuat(const Vector3 & axis, float rad)
	{
		float t2 = rad * .5f;
		float st2 = sin(t2);
		return Quaternion(axis.x * st2, axis.y * st2, axis.z * st2, cos(t2));
	}

	Quaternion MathUtil::EulerRadToQuat(const Vector3 & eulerRad)
	{
		return EulerRadToQuat(eulerRad.x, eulerRad.y, eulerRad.z);
	}

	Quaternion MathUtil::EulerRadToQuat(float yaw, float pitch, float roll)
	{
		float cx = std::cos(yaw / 2);
		float sx = std::sin(yaw / 2);
		float cy = std::cos(pitch / 2);
		float sy = std::sin(pitch / 2);
		float cz = std::cos(roll / 2);
		float sz = std::sin(roll / 2);

		return Quaternion(
			sx * sz * cy + cx * cz * sy,
			sx * cz * cy + cx * sz * sy,
			cx * sz * cy - sx * cz * sy,
			cx * cz * cy - sx * sz * sy
		);
	}

}