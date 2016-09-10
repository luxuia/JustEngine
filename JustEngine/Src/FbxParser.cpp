#include "FbxParser.h"
#include "GameObject.h"
#include "Mesh.h"

namespace JustEngine
{
	void FbxParser::LoadScene(const std::string & filePath, GameObjectPtr rootNode)
	{
		mFbxManager = FbxManager::Create();
		auto ios = FbxIOSettings::Create(mFbxManager, IOSROOT);
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
	}

	std::shared_ptr<Mesh> FbxParser::CreateMesh(GameObjectPtr node, FbxNode * fbxNode)
	{
		Mesh::Ptr mesh = nullptr;

		FbxMesh* fbxMesh = static_cast<FbxMesh*>(fbxNode->GetNodeAttribute());


		return mesh;
	}

}