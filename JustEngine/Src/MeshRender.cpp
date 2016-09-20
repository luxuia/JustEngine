#include "MeshRender.h"
#include "GraphicsCore.h"
#include "GameObject.h"

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
		cb.world = mOwner.lock()->GetWorldMatrix();
		cb.view.LookAt(Vector3(0, 0, -0.1), Vector3(0, 0, 0), Vector3::Up);
		cb.proj.PerspectiveFovLH(3.1415f/2, DEFAULT_RECT_WIDTH/DEFAULT_RECT_HEIGHT, 0.01f, 1000.f);

		//// Test Code
		//Vector4 TestPos = Vector4(1, 1, 1, 1);
		//TestPos = TestPos * cb.world;
		//TestPos = TestPos * cb.view;
		//TestPos = TestPos * cb.proj;
		//Utility::Printf("%f %f %f", TestPos.x, TestPos.y, TestPos.z);
		context->UpdateSubresource(mpConstantBuffer, NULL, 0, &cb, 0, 0);
		context->VSSetConstantBuffers(0, 1, &mpConstantBuffer);

		mMaterial->Bind(context);
		mMesh->BindDraw(context);
	}
}