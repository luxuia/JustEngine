#pragma once
#include "Math/Vector.h"

namespace JustEngine
{
	using namespace JustEngine;

	struct MeshP3
	{
		Vector3 Position;
	};

	struct MeshP3N3
	{
		Vector3 Position;
		Vector3 Normal;
	};

	struct MeshP3C4
	{
		Vector3 Position;
		Vector4 Color;
	};

	struct MeshP3N3U2
	{
		Vector3 Position;
		Vector3 Normal;
		Vector2 UV;
	};

}
