#pragma once

#include "pch.h"

namespace Base
{
	// TODO
	class DLL_EXPORT Serializable
	{
	public:
		ObjTypePtr( Serializable );

		virtual bool Load( const void* wrapper ) {};

		virtual bool Save( const void* wrapper ) {};
	};
}