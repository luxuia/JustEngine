#pragma once

#include "pch.h"
#include "Singleton.h"

namespace JustEngine
{
	class Octree;

	class DLL_EXPORT SceneManager :public Singleton<SceneManager>
	{
	public:
		void InitWorld(float width, float length, float height, int maxDepth);

		void Add

	private:
		Octree* tree;
	};
	
}