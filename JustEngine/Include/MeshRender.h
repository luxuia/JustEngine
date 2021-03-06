#pragma once

#include "pch.h"
#include "Mesh.h"
#include "Material.h"
#include "Component.h"
#include "Matrix.h"

namespace JustEngine
{
	class Camera;
	class DLL_EXPORT MeshRender : public Component
	{
	public:
		struct ConstantBuffer
		{
			Matrix4 world;
			Matrix4 view;
			Matrix4 proj;
		};

		ObjTypePtr( MeshRender );

		MeshRender();

		static Ptr Create();

		std::shared_ptr<Mesh> mMesh;
		Material::Ptr mMaterial;

		ID3D11InputLayout* mVertexLayout;
		ID3D11Buffer* mpConstantBuffer;

		virtual void Setup();
		virtual void Render(const Camera& camera);
	};
}