#include "pch.h"
#include "GameObject.h"
#include "Component.h"

namespace Base
{
	GameObject::Ptr GameObject::Create(const std::string& name )
	{
		return std::make_shared<GameObject>(name);
	}

	GameObject::GameObject( const std::string& name ) : Entity( name ), mLocalScale(1.f, 1.f, 1.f)
	{
		mTypeIndex = typeid(GameObject);
	}

	GameObject::~GameObject()
	{
		RemoveAllChilds();
		RemoveAllComponent();
	}

	GameObject::Ptr GameObject::GetParent() const
	{
		return mParent.lock();
	}


	size_t GameObject::GetChildCount()const
	{
		return mChilds.size();
	}

	void GameObject::AddChild( const Ptr &node )
	{
		mChilds.push_back( node );
	}

	void GameObject::RemoveChild( const Ptr& node )
	{
		for (size_t i = 0; i < mChilds.size(); ++i)
		{
			if (mChilds[i] == node)
			{
				node->RemoveFromParent();

				mChilds.erase( mChilds.begin() + i);

				return;
			}
		}
		//LOG WARNING
	}

	void GameObject::RemoveAllChilds()
	{
		Ptr node;
		while (mChilds.size() > 0)
		{
			node = mChilds.back();
			mChilds.pop_back();

			node->SetParnet( nullptr );
		}
	}

	GameObject::Ptr GameObject::GetChildAt( uint32_t idx )const
	{
		ASSERT( idx < mChilds.size() );

		return mChilds[idx];
	}

	void GameObject::SetParnet(const Ptr& parent )
	{
		mParent = parent;
		
		FreshData();
	}

	void GameObject::RemoveFromParent()
	{
		SetParnet( nullptr );
	}

	GameObject::Ptr GameObject::FindChildRecursively( const std::string &name ) const
	{
		GameObject::Ptr node;
		for (uint32_t i = 0; i < mChilds.size(); ++i)
		{
			node = mChilds[i]->FindChildRecursively( name );
			if (node != nullptr) return node;
		}
		return nullptr;
	}

	bool GameObject::AddComponent( const std::shared_ptr<Component> &ptr )
	{
		mComponents.emplace( ptr->GetTypeIndex(), ptr );
		return true;
	}

	bool GameObject::RemoveComponent(const std::shared_ptr<Component>& ptr)
	{
		return false;
	}

	std::shared_ptr<Component> GameObject::GetComponent( std::type_index type ) const
	{
		auto it = mComponents.find( type );
		if (it != mComponents.end())
		{
			return it->second;
		}
		return nullptr;
	}

	void GameObject::RemoveAllComponent()
	{
		auto it = mComponents.begin();
		while (it != mComponents.end()) 
		{
			it->second.reset();
		}
		mComponents.clear();
	}

	template<class T>
	std::shared_ptr<T> GameObject::GetComponent() const
	{
		auto it = mComponents.find( typeid(T) );
		if (it != mComponents.end())
		{
			return it->second;
		}
		return nullptr;
	}

	Matrix4 GameObject::GetLocalMatrix() const
	{
		return mLocalMatrix;
	}

	void GameObject::FreshData()
	{
	}

	Matrix4 GameObject::GetWorldMatrix() const
	{
		return mWorldMatrix;
	}

	Vector3 GameObject::GetLocalPosition() const
	{
		return mLocalPosition;
	}
	Vector3 GameObject::GetLocalScale() const
	{
		return mLocalScale;
	}
	Vector3 GameObject::GetLocalRotation() const
	{
		return mLocalEulerAngle;
	}
	Vector3 GameObject::GetWorldPosition() const
	{
		return mWorldPosition;
	}
	Vector3 GameObject::GetWorldScale() const
	{
		return mWorldScale;
	}
	Vector3 GameObject::GetWorldRotation() const
	{
		return mWorldEulerAngle;
	}


}