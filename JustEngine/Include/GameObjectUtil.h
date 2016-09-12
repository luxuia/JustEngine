#include "pch.h"
#include "Mesh.h"
#include "GameObject.h"
#include <string>

namespace JustEngine
{
	class DLL_EXPORT GameObjectUtil
	{
	public:
		static GameObject::Ptr CreateCube(const std::string& name);
	};

	GameObject::Ptr GameObjectUtil::CreateCube(const std::string& name)
	{
		auto renderer = MeshRender::Create();

		Vector3 vertices[] = {
			Vector3(-1.0f, 1.0f, -1.0f),
			Vector3(1.0f, 1.0f, -1.0f),
			Vector3(1.0f, 1.0f, 1.0f),
			Vector3(-1.0f, 1.0f, 1.0f),

			Vector3(-1.0f, -1.0f, -1.0f),
			Vector3(1.0f, -1.0f, -1.0f),
			Vector3(1.0f, -1.0f, 1.0f),
			Vector3(-1.0f, -1.0f, 1.0f),
		};
		Vector4 colors[] = {
			Vector4(0.0f, 0.0f, 1.0f, 1.0f),
			Vector4(0.0f, 1.0f, 0.0f, 1.0f),
			Vector4(0.0f, 1.0f, 1.0f, 1.0f),
			Vector4(1.0f, 0.0f, 0.0f, 1.0f),

			Vector4(1.0f, 0.0f, 1.0f, 1.0f),
			Vector4(1.0f, 1.0f, 0.0f, 1.0f),
			Vector4(1.0f, 1.0f, 1.0f, 1.0f),
			Vector4(0.0f, 0.0f, 0.0f, 1.0f),
		};

		uint32_t indices[] = {
			3,1,0,
			2,1,3,

			0,5,4,
			1,5,0,

			3,4,7,
			0,4,3,

			1,6,5,
			2,6,1,

			2,7,6,
			3,7,2,

			6,4,5,
			7,4,6,
		};

		renderer->mMesh = Mesh::Create("");

		renderer->mMesh->SetupBuffers(indices, ARRAY_NUM(indices), vertices, ARRAY_NUM(vertices), colors, ARRAY_NUM(colors));

		renderer->mMaterial = Material::Create();

		auto obj = GameObject::Create(name);

		obj->AddComponent(renderer);

		return obj;
	}
}