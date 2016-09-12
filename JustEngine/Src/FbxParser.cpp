#include "FbxParser.h"
#include "GameObject.h"
#include "Mesh.h"

namespace JustEngine
{
	void FbxParser::LoadScene(const std::string & filePath, GameObjectPtr rootNode)
	{
		mFbxManager = FbxManager::Create();
		auto ios = FbxIOSettings::Create(mFbxManager, IOSROOT);
		mFbxManager->SetIOSettings(ios);

		auto importer = FbxImporter::Create(mFbxManager, "");
		auto pos = filePath.find_last_of("/");
		mFbxFolder = (std::string::npos == pos) ? "" : filePath.substr(0, pos + 1);

		Utility::Printf("FbxFolder %s", mFbxFolder.c_str());

		if (importer->Initialize(filePath.c_str(), -1, mFbxManager->GetIOSettings()))
		{
			mFbxScene = FbxScene::Create(mFbxManager, "");
			bool result = importer->Import(mFbxScene);
			importer->Destroy();


			if (result)
			{
				auto& globalSetting = mFbxScene->GetGlobalSettings();

				FbxGeometryConverter geomConverter(mFbxManager);
				geomConverter.Triangulate(mFbxScene, true);

				auto fbxRootNode = mFbxScene->GetRootNode();

				if (fbxRootNode)
				{
					for (int i = 0; i < fbxRootNode->GetChildCount(); ++i)
					{
						LoadNode(rootNode, fbxRootNode->GetChild(i));
					}
					rootNode->FreshData();
				}
			}
		}
		else
		{
			auto status = importer->GetStatus();
			auto str = status.GetErrorString();
			Utility::Printf("FBX File Cant Load %s %s", filePath.c_str(), str);
		}
	}

	void FbxParser::LoadNode(GameObjectPtr node, FbxNode * fbxNode)
	{
		GameObject::Ptr childNode = GameObject::Create(fbxNode->GetName());

		node->AddChild(childNode);

		FbxNodeAttribute* fbxNodeAttr = fbxNode->GetNodeAttribute();

		if (fbxNodeAttr != nullptr)
		{
			auto attrType = fbxNodeAttr->GetAttributeType();
			if (attrType == FbxNodeAttribute::eMesh)
			{
				LoadMesh(childNode, fbxNode);
			}
		}
	}

	void FbxParser::LoadMesh(GameObjectPtr node, FbxNode * fbxNode)
	{
		FbxMesh* fbxMesh = static_cast<FbxMesh*>(fbxNode->GetNodeAttribute());

		auto mesh = CreateMesh(node, fbxNode);

		auto renderer = MeshRender::Create();
		renderer->mMesh = mesh;
		renderer->mMaterial = Material::Create();
		node->AddComponent(renderer);
	}

	std::shared_ptr<Mesh> FbxParser::CreateMesh(GameObjectPtr node, FbxNode * fbxNode)
	{
		Mesh::Ptr mesh = Mesh::Create(fbxNode->GetName());

		FbxMesh* fbxMesh = static_cast<FbxMesh*>(fbxNode->GetNodeAttribute());

		int polygonCount = fbxMesh->GetPolygonCount();
		int indicesCount = polygonCount * 3;
			
		mesh->Positions.Data.reserve(indicesCount * 3);
		mesh->Indices.Data.reserve(indicesCount);

		for (int i = 0; i < polygonCount; ++i) {
			ASSERT(fbxMesh->GetPolygonSize(i) <= 3,  "Error: triangulate %s", mesh->GetName());

			for (int jj = 0; jj < 3; ++jj) {
				int ctrPointIdx = fbxMesh->GetPolygonVertex(i, jj);

				auto position = fbxMesh->GetControlPointAt(ctrPointIdx);
				mesh->Positions.Data.push_back((double*)&position);

				int indices = i * 3 + jj;
				mesh->Indices.Data.push_back(indices);
			}
		}
		mesh->UpdateBuffer();
		return mesh;
	}

}