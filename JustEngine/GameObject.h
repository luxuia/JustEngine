#pragma once

#include <unordered_map>
#include <vector>

#include "pch.h"
#include "Entity.h"
#include "Serializable.h"
#include "Component.h"
#include "MeshRender.h"

namespace JustEngine
{
	using namespace Math;

	class OcTreeNode;

	// To destory a scenenode.
	// Call node.RemoveFromParent + node.RemoveFromOcTree(true) + node=null
	// This node together with all it's childs will be destoried.
	class DLL_EXPORT GameObject :public Entity, public std::enable_shared_from_this<GameObject>, public Serializable
	{
		friend class OcTreeNode;
	public :
		ObjTypePtr( GameObject );

		static Ptr Create( const std::string & name );

		GameObject( const std::string& name );
		virtual ~GameObject();

		//virtual void OnEnable();
		//virtual void OnDisable();
		//virtual void Update();


		void FreshData();

		Matrix4 GetWorldMatrix() const;
		Matrix4 GetLocalMatrix( ) const;
		//Matrix4 GetInvertWorldMatrix( ) const;

		Vector3 GetLocalPosition() const;
		Vector3 GetWorldPosition() const;
		Vector3 GetLocalScale() const;
		Vector3 GetWorldScale() const;
		Vector3 GetLocalRotation() const;
		Vector3 GetWorldRotation() const;

		//void SetLocalPosition( Vector3& pos );
		//void SetLocalScale( Vector3& scale );
		//void SetLocalRotate( Vector3& eulerAngle );
		
		Ptr GetParent() const;
		
		void AddChild(const Ptr &node);
		void RemoveChild( const Ptr& node );

		Ptr GetChildAt( uint32_t idx ) const;

		void RemoveFromParent();

		void SetParent( const Ptr& parent );

		void RemoveAllChilds();

		//void Replace( const Ptr& node );

		//Ptr FindChild( const std::string &name )const;
		Ptr FindChildRecursively( const std::string &name ) const;

		uint32_t GetChildCount() const;

		bool AddComponent(const Component::Ptr& ptr);
		bool RemoveComponent(const Component::Ptr& ptr);

		template<class T>
		std::shared_ptr<T> GetComponent() const;
		std::shared_ptr<Component> GetComponent( std::type_index type ) const;

		void RemoveAllComponent();

	protected:
		std::weak_ptr<OcTreeNode> mOcTreeNode;

		std::weak_ptr<GameObject> mParent;

		std::vector<Ptr> mChilds;

		std::unordered_map<std::type_index, Component::Ptr> mComponents;

		Matrix4 mWorldMatrix;

		Matrix4 mLocalMatrix;

		Vector3 mLocalPosition;
		Vector3 mLocalScale;
		Vector3 mLocalEulerAngle;

		Vector3 mWorldPosition;
		Vector3 mWorldScale;
		Vector3 mWorldEulerAngle;
	};

}