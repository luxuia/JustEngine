#pragma once

#include "pch.h"
#include "TypeComparable.h"

namespace Base
{
	class DLL_EXPORT Entity : public TypeComparable
	{
	public:
		ObjTypePtr( Entity );

		static Ptr Create( const std::string &name );
		Entity( const std::string &name );
		Entity();

		virtual ~Entity() = default;

		virtual std::type_index GetTypeIndex() const;

		std::string GetName() const;

		size_t GetHashCode() const;

		size_t SetName( const std::string & name );

	protected:
		std::type_index mTypeIndex;

		std::string mName;

		size_t mHashCode;
	};
}