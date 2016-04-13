#pragma once

#include <typeindex>
#include "pch.h"

namespace Base
{
	class DLL_EXPORT TypeComparable
	{
	public:
		virtual std::type_index GetTypeIndex() const = 0;
	};
}