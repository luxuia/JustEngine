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

	auto obj = GameObject::Create( "Camera" );
	auto camera = Camera::Create();
	camera->SetPerspective(100.f, 100.f, 1.f, 1000.f);

	obj->AddComponent(camera);
	
	obj->SetParent(Root);

	FbxParser::Instance()->LoadScene("Scene/BnHFemale.fbx", Root);

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
	auto mesh = Root->FindChildRecursively("Tank.004");

	static float radian = 0;
	radian += 0.1f;

	Quaternion quat = MathUtil::AxisRadToQuat(Vector3(1,1,1), radian);
	mesh->SetLocalRotate(quat);

	auto renderer = mesh->GetComponent(typeid(MeshRender));

	std::dynamic_pointer_cast<MeshRender>(renderer)->Render();
}