#include "GameObject.h"
#include "Utility.h"

namespace JustEngine
{
	GameObject::Ptr GameObject::Create(const std::string& name )
	{
		return std::make_shared<GameObject>(name);
	}

	GameObject::GameObject( const std::string& name ) : Entity( name ), mLocalScale(1.f, 1.f, 1.f)
	{
		mTypeIndex = typeid(GameObject);
		//mComponents = std::unordered_map<std::type_index, std::shared_ptr<Component>>();
		//SetLocalScale(Vector3::One);
		//SetLocalPosition(Vector3::Zero);
		//SetLocalRotate(Vector3::Zero);
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

			node->RemoveFromParent();
		}
	}

	GameObject::Ptr GameObject::GetChildAt( uint32_t idx )const
	{
		ASSERT( idx < mChilds.size() );

		return mChilds[idx];
	}

	void GameObject::SetParent(const Ptr& parent )
	{
		if (mParent.lock() == parent) return;
		if (mParent.lock()!= nullptr) RemoveFromParent();

		mParent = parent;
		parent->AddChild(shared_from_this());
		FreshData();
	}

	void GameObject::RemoveFromParent()
	{
		if (mParent.lock() != nullptr)
		{
			mParent.lock()->RemoveChild(shared_from_this());
		}
	}

	GameObject::Ptr GameObject::FindChildRecursively( const std::string &name ) const
	{
		GameObject::Ptr node;
		for (uint32_t i = 0; i < mChilds.size(); ++i)
		{
			if (name == mChilds[i]->GetName())
			{
				return mChilds[i];
			}
			node = mChilds[i]->FindChildRecursively(name);
			if (node != nullptr) return node;
		}
		return nullptr;
	}

	bool GameObject::AddComponent(const Component::Ptr& ptr )
	{
		mComponents.emplace(ptr->GetTypeIndex(), ptr);
		ptr->OnAttach(shared_from_this());
		return true;
	}

	bool GameObject::RemoveComponent(const Component::Ptr& ptr)
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


	template<class T>
	std::shared_ptr<T> GameObject::GetComponent() const
	{
		auto it = mComponents.find(typeid(T));
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
			it->second->OnDetach(shared_from_this());
			it->second.reset();
			it++;
		}
		mComponents.clear();
	}

	Matrix4 GameObject::GetLocalMatrix() const
	{
// 		if (mTransformDirty)
// 		{
// 			this->FreshData();
// 		}
// 	
		return mLocalMatrix;
	}

	void GameObject::FreshData()
	{
		mLocalMatrix = Matrix4::identity;
		mWorldMatrix = Matrix4::identity;
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

	void GameObject::SetLocalScale(const Vector3& scale)
	{
		if (mTransformDirty || scale != mLocalScale)
		{
			mLocalScale = scale;
			mTransformDirty = true;

			FreshData();
		}
	}

	void GameObject::SetLocalRotate(const Vector3& eulerAngle)
	{
		if (mTransformDirty || eulerAngle != mLocalEulerAngle)
		{
			mLocalEulerAngle = eulerAngle;
			mTransformDirty = true;

			FreshData();
		}
	}

	void GameObject::SetLocalPosition(const Vector3& pos)
	{
		if (mTransformDirty || pos != mLocalPosition) 
		{
			mLocalPosition = pos;
			mTransformDirty = true;



			FreshData();
		}
	}

}