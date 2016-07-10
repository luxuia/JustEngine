#pragma once

#include "pch.h"
#include "Mesh.h"
#include "Material.h"
#include "Component.h"

namespace JustEngine
{
	class DLL_EXPORT MeshRender : public Component
	{
	public:
		ObjTypePtr( MeshRender );

		MeshRender();

		static Ptr Create();

		std::shared_ptr<BaseMesh> mMesh;
		Material::Ptr mMaterial;

		ID3D11InputLayout* mVertexLayout;

		virtual void Setup();
		virtual void Render();
	};
}