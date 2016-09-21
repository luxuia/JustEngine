#include "GameObject.h"
#include "Utility.h"
#include "Matrix.h"

namespace JustEngine
{
	const std::string GameObject::TransfromChange = "TransfromChange";

	GameObject::Ptr GameObject::Create(const std::string& name )
	{
		return std::make_shared<GameObject>(name);
	}

	GameObject::GameObject( const std::string& name ) : Entity( name ), mLocalScale(1.f, 1.f, 1.f)
	{
		mTypeIndex = typeid(GameObject);
		//mComponents = std::unordered_map<std::type_index, std::shared_ptr<Component>>();
		//SetLocalScale(Vector3::One);
		SetLocalPosition(Vector3::Zero);
		SetLocalRotate(Quaternion(.0, .0, .0, 1.));

		mSignal = Signal::Create();
		mSignal->CreateSlot(TransfromChange);
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

	// 设完localTransform后再调用
	// 免费的计算worldTrans的机会
	void GameObject::SetParent(const Ptr& parent, bool freshData)
	{
		if (mParent.lock() == parent) return;
		if (mParent.lock()!= nullptr) RemoveFromParent();

		mParent = parent;
		parent->AddChild(shared_from_this());
		if (freshData) FreshData();
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
		auto index = ptr->GetTypeIndex();
		auto it = mComponents.find(index);
		if (it != mComponents.end()) {
			it->second.reset();
			return true;
		}
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
			// component will auto destroyed when share_ptr's reference count down to zero
			it->second.reset();
			it++;
		}
		mComponents.clear();
	}

	const JustEngine::Signal::Ptr& GameObject::GetSignal() const
	{
		return mSignal;
	}

	const Matrix4& GameObject::GetLocalMatrix() const
	{
// 		if (mTransformDirty)
// 		{
// 			this->FreshData();
// 		}
// 	
		return mLocalMatrix;
	}

	void GameObject::FreshData(bool bForce)
	{
		if (mTransformDirty || bForce)
		{
			mLocalMatrix = Matrix4::Transform(mLocalPosition) * Matrix4::Scale(mLocalScale)*Matrix4::Rotate(mLocalRotation);
			if (mParent.expired()) {
				mWorldMatrix = mLocalMatrix;
				mWorldPosition = mLocalPosition;
				mWorldRotation = mLocalRotation;
				mWorldScale = mLocalScale;
			}
			else {
				auto worldMat = mParent.lock()->GetWorldMatrix();
				mWorldMatrix = worldMat * mLocalMatrix;
				mWorldPosition = mLocalPosition * worldMat;
				mWorldScale = mParent.lock()->GetWorldScale().Multi(mLocalScale);
				mWorldRotation = mLocalRotation*mParent.lock()->GetWorldRotation();
			}
			for (uint32_t i = 0; i < mChilds.size(); ++i) {
				mChilds[i]->FreshData(true);
			}
			mTransformDirty = false;
			mSignal->Emit(TransfromChange, shared_from_this());
		}
	}

	const Matrix4& GameObject::GetWorldMatrix() const
	{
		return mWorldMatrix;
	}

	const Vector3& GameObject::GetLocalPosition() const
	{
		return mLocalPosition;
	}
	const Vector3& GameObject::GetLocalScale() const
	{
		return mLocalScale;
	}
	const Quaternion& GameObject::GetLocalRotation() const
	{
		return mLocalRotation;
	}
	const Vector3& GameObject::GetWorldPosition() const
	{
		return mWorldPosition;
	}
	const Vector3& GameObject::GetWorldScale() const
	{
		return mWorldScale;
	}
	const Quaternion& GameObject::GetWorldRotation() const
	{
		return mWorldRotation;
	}

	void GameObject::SetLocalScale(const Vector3& scale)
	{
		if (mTransformDirty || scale != mLocalScale)
		{
			mLocalScale = scale;
			mTransformDirty = true;
		}
	}

	void GameObject::SetLocalRotate(const Quaternion& rotation)
	{
		if (mTransformDirty || mLocalRotation != rotation )
		{
			mLocalRotation = rotation;
			mTransformDirty = true;
		}
	}

	void GameObject::SetLocalPosition(const Vector3& pos)
	{
		if (mTransformDirty || pos != mLocalPosition) 
		{
			mLocalPosition = pos;
			mTransformDirty = true;
		}
	}

}