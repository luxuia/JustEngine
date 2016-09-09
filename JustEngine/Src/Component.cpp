#include "pch.h"
#include "Component.h"
#include "GameObject.h"

namespace JustEngine
{	
	Component::Component( ) : mTypeIdex( typeid(Component) )
	{
	}

	Component::~Component()
	{

	}

	std::type_index Component::GetTypeIndex() const
	{
		return mTypeIdex;
	}

	GameObject::Ptr Component::GetOwner()
	{
		return mOwner.lock();
	}

	void Component::Update(float deltaT) const
	{
	}

	void Component::OnAttach( const std::shared_ptr<GameObject> &node )
	{
		//ASSERT(!mOwner.expired());
		mOwner = node;
	}

	void Component::OnDetach( const std::shared_ptr<GameObject> &node )
	{
		ASSERT( mOwner.lock() == node );
	}

	void Component::OnDestroy()
	{
	}
}