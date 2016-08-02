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
	MeshP3C4 vertices[] = {
		{ Vector3(1.f, 1.f, -1.f), Vector4(0.f, 0.f, 1.f, 1.f)},
		{ Vector3(1.f, -1.f, -1.f), Vector4(1.f, 0.f, 1.f, 1.f) },
		{ Vector3(-1.f, -1.f, -1.f), Vector4(0.f, 1.f, 1.f, 1.f) },
		{ Vector3(-1.f, 1.f, -1.f), Vector4(1.f, 1.f, 1.f, 1.f) },

		{ Vector3(1.f, 1.f, 1.f), Vector4(1.f, 0.f, 0.f, 1.f) },
		{ Vector3(1.f, -1.f, 1.f), Vector4(0.f, 1.f, 0.f, 1.f) },
		{ Vector3(-1.f, -1.f, 1.f), Vector4(1.f, 1.f, 0.f, 1.f) },
		{ Vector3(-1.f, 1.f, 1.f), Vector4(0.f, 0.f, 0.f, 1.f) },
	};

	uint32_t indices[] = {
		0, 1, 2,
		0, 2, 3,

		0, 3, 7,
		0, 7, 4,

		0, 4, 5,
		0, 5, 1,

		4, 6, 5,
		4, 7, 6,

		1, 6, 2,
		1, 5, 6,

		3, 6, 7,
		3, 2, 6,
	};

	mesh->mMesh = Mesh<MeshP3C4>::Create("", vertices, ARRAY_NUM(vertices), indices, ARRAY_NUM(indices));
	mesh->mMaterial = Material::Create();

	node->AddComponent(mesh);

	node->SetParent(Root);
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
	auto mesh = Root->FindChildRecursively("SquareMesh");

	auto renderer = mesh->GetComponent(typeid(MeshRender));

	std::dynamic_pointer_cast<MeshRender>(renderer)->Render();
}