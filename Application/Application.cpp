// Application.cpp : 定义控制台应用程序的入口点。
//

#include "pch.h"
//#include <SFML/Window.hpp>
#include "GameCore.h"
#include "GameObject.h"
#include "Component.h"
#include "Camera.h"
#include "MeshRender.h"

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

	auto node = GameObject::Create("SquareMesh");

	auto mesh = MeshRender::Create();
	MeshP3 vertices[] = {
		{ Vector3(0.5f, 0.5f, 1.f) },
		{ Vector3(0.5f, -0.5f, 1.f) },
		{ Vector3(-0.5f, -0.5f, 1.f) },
		{ Vector3(-0.5f, 0.5f, 1.f) },
	};

	uint32_t indices[] = {
		1,2,0,3
	};

	mesh->mMesh = Mesh<MeshP3>::Create("", vertices, ARRAY_NUM(vertices), indices, ARRAY_NUM(indices));
	mesh->mMaterial = Material::Create();

	node->AddComponent(mesh);

	node->SetParent(Root);
}

void App::CleanUp()
{

}

void App::Update(float deltaTime)
{

}

void App::RenderScene()
{
	auto mesh = Root->FindChildRecursively("SquareMesh");

	auto renderer = mesh->GetComponent(typeid(MeshRender));

	std::dynamic_pointer_cast<MeshRender>(renderer)->Render();
}