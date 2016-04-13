#pragma once

#include <unordered_map>
#include <vector>

#include "pch.h"
#include "Entity.h"

namespace Base
{
	class Component;
	class OcTreeNode;

	// To destory a scenenode.
	// Call node.RemoveFromParent + node.RemoveFromOcTree(true) + node=null
	// This node together with all it's childs will be destoried.
	class DLL_EXPORT GameObject :public Entity, public std::enable_shared_from_this<GameObject>
	{
		friend class OcTreeNode;
	public :
		ObjTypePtr( GameObject );

		static Ptr Create( const std::string & name );

	protected:
		std::weak_ptr<OcTreeNode> mOcTreeNode;

		std::weak_ptr<GameObject> mParent;

		std::vector<Ptr> mChilds;

		std::unordered_map<std::type_index, std::shared_ptr<Component>> mComponents;
	};
}