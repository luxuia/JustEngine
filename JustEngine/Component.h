#pragma once

#include "pch.h"
#include "TypeComparable.h"
#include "Serializable.h"

namespace Base
{
	class DLL_EXPORT Component :public TypeComparable, public Serializable
	{
		friend class GameObject;

	public:
		Component();
		~Component();

		virtual std::type_index GetTypeIndex() const;

		std::shared_ptr<GameObject> GetOwner();

		virtual void Update( float deltaT ) const;

	protected:
		std::type_index mTypeIdex;

		std::weak_ptr<GameObject> mOwner;

		virtual void OnAttach( const std::shared_ptr<GameObject> &node );
		virtual void OnDetach( const std::shared_ptr<GameObject> &node );

		virtual void OnDestroy();
	};
}