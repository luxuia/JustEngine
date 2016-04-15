#pragma once

#include "pch.h"
#include "Mesh.h"
#include "Material.h"

namespace Graphics
{
	template<class T> 
	class DLL_EXPORT MeshRender  
	{
	public:
		ObjTypePtr( MeshRender );

		static Ptr Create();

		Base::Mesh<T>::Ptr mMesh;
		Material::Ptr mMaterial;
	};
}