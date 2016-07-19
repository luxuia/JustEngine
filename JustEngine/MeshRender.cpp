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

		D3D11_BUFFER_DESC db = {};
		db.Usage = D3D11_USAGE_DEFAULT;
		db.ByteWidth = sizeof(ConstantBuffer);
		db.CPUAccessFlags = 0;
		db.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		
		g_Device->CreateBuffer(&db, nullptr, &mpConstantBuffer);
	}

	void MeshRender::Setup()
	{

	}

	void MeshRender::Render()
	{
		ID3D11DeviceContext* context = nullptr;
		g_Device->GetImmediateContext(&context);

		ConstantBuffer cb;
		cb.world.Identity();
		cb.proj = Matrix4
		cb.view.Identity();
		context->UpdateSubresource(mpConstantBuffer, NULL, 0, &cb, 0, 0);
		context->VSSetConstantBuffers(0, 1, &mpConstantBuffer);

		mMaterial->Bind(context);
		mMesh->BindDraw(context);
	}
}