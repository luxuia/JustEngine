#pragma once

#include "pch.h"

namespace JustEngine
{
	class OctreeNode;

	class DLL_EXPORT SceneNode
	{
		friend class OctreeNode;
	public :
		ObjTypePtr(SceneNode);

		static Ptr Create(const std::string &name);

		std::weak_ptr<OctreeNode> m_OctreeNode;

		
	};
}