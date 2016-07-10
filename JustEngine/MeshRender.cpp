#include "MeshRender.h"
#include "GraphicsCore.h"

namespace JustEngine
{
	using namespace Graphics;

	std::shared_ptr<MeshRender> MeshRender::Create()
	{
		return std::make_shared<MeshRender>();
	}
	
	MeshRender::MeshRender() : Component()
	{
		mTypeIdex = typeid(MeshRender);
	}

	void MeshRender::Setup()
	{

	}

	void MeshRender::Render()
	{
		ID3D11DeviceContext* context = nullptr;
		g_Device->GetImmediateContext(&context);

		mMaterial->Bind(context);
		mMesh->BindDraw(context);
	}
}