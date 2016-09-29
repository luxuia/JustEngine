#pragma once

#include "pch.h"
#include "Singleton.h"

namespace JustEngine
{
	enum class FbxImportFlags : unsigned int
	{
		UV = 0x0001,
		NORMAL = 0x0002,
		TANGENT = 0x0004,
	};

	struct FbxImportOptions
	{
	
	};

	class GameObject;
	class Mesh;
	class FbxScene;
	class FbxManager;
	class FbxNode;
	class DLL_EXPORT FbxParser : public Singleton<FbxParser>
	{
		using GameObjectPtr = const std::shared_ptr<GameObject> &;

	protected:
		FbxScene* mFbxScene = nullptr;
		FbxManager* mFbxManager = nullptr;

		std::string mFbxFolder;

	public:
		using Ptr = std::shared_ptr<FbxParser>;

		void LoadScene(const std::string& filePath, GameObjectPtr rootNode);

	protected:
		void LoadNode(GameObjectPtr node, FbxNode* fbxNode);
		void LoadMesh(GameObjectPtr node, FbxNode* fbxNode);

		std::shared_ptr<Mesh> CreateMesh(GameObjectPtr node, FbxNode* fbxNode);
		void ApplyLocalTransform(GameObjectPtr node, FbxNode* fbxNode);

	};
}