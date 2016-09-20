// Application.cpp : 定义控制台应用程序的入口点。
//

#include "pch.h"
//#include <SFML/Window.hpp>
#include "GameCore.h"
#include "Component.h"
#include "Camera.h"
#include "MeshRender.h"
#include "GameObjectUtil.h"
#include "FbxParser.h"
#include "MathUtil.h"

using namespace GameCore;
using namespace JustEngine;

const int MAX_FIX_LOOP_NUM = 5;
const float FIX_UPDATE_TICK = 1000.f/60.f;

#pragma comment(lib, "dxguid.lib")

class App : public IGameApp
{
public:

	App() = default;

	virtual void Start( void ) override;

	virtual void CleanUp( void ) override;

	virtual void Update( float deltaTime ) override;

	virtual void RenderScene( void ) override;

	GameObject::Ptr Root;
};

int _tmain(int argc, wchar_t** argv[])
{
	CREATE_APP( App );
	return 0;
}

void App::Start()
{	
	Root = GameObject::Create("SceneRoot");

	Root->SetLocalPosition(Vector3(.0, -50, 100.));
	//Root->SetLocalRotate(MathUtil::AxisRadToQuat(1, 0, 0, 90 * MathUtil::RadToDeg));// *MathUtil::AxisRadToQuat(0, 1, 0, radian));
	Root->SetLocalScale(Vector3(0.5, 0.5, 0.5));
	Root->FreshData(false);


	auto obj = GameObject::Create( "Camera" );
	auto camera = Camera::Create();
	camera->SetPerspective(100.f, 100.f, 1.f, 1000.f);

	obj->AddComponent(camera);
	obj->SetParent(Root);

	FbxParser::Instance()->LoadScene("Scene/M_A01.fbx", Root);

	//auto node = GameObjectUtil::CreateCube("SquareMesh");
	//node->SetParent(Root);
}

void App::CleanUp()
{

}

void App::Update(float deltaTime)
{
	auto camera = Root->FindChildRecursively("Camera");
}

void App::RenderScene()
{		
	static float radian = 0;
	radian += 0.1f;
	auto renderers = Root->GetComponentsInChilds<MeshRender>();


	for (uint32_t i = 0; i < renderers.size(); ++i)
	{
		//auto mesh = Root->FindChildRecursively("MA-hand-A01");

		//auto renderer = mesh->GetComponent(typeid(MeshRender));

		auto renderer = renderers[ i ];

		Quaternion quat = MathUtil::AxisRadToQuat(Vector3(1, 1, 1), radian);
		renderer->GetOwner()->SetLocalRotate(quat);
		renderer->GetOwner()->FreshData();

		renderer->Render();
	}
}