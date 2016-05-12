#pragma once

#include "pch.h"
#include "Mesh.h"
#include "Material.h"

namespace Graphics
{
	using namespace Base;

	template<class T> 
	class DLL_EXPORT MeshRender  
	{
	public:
		ObjTypePtr( MeshRender );

		static Ptr Create();

		std::shared_ptr<Mesh<T>> mMesh;
		Material::Ptr mMaterial;
	};
}