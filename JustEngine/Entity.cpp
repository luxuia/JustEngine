#include "Entity.h"
#include "Hash.h"

namespace Base
{
	Entity::Ptr Entity::Create( const std::string &name )
	{
		return std::make_shared<Entity>( name );
	}

	Entity::Entity( ) :mTypeIndex( typeid(Entity) )
	{
		SetName( "NoneName" );
	}

	Entity::Entity( const std::string &name ) :mTypeIndex(typeid(Entity))
	{
		SetName( name );
	}

	std::type_index Entity::GetTypeIndex() const
	{
		return mTypeIndex;
	}

	std::string Entity::GetName() const
	{
		return mName;
	}

	size_t Entity::GetHashCode() const
	{
		return mHashCode;
	}

	size_t Entity::SetName(const std::string& name)
	{
		mName = name;
		mHashCode = Utility::HashArray( name.c_str(), name.length() );
		return mHashCode;
	}
}