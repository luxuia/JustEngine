#pragma once

#include "Macros.h"

namespace JustEngine
{
	class DLL_EXPORT Buffer
	{
	protected:
		bool mDirty = true;
	public:
		virtual void DeleteBuffer() = 0;

		bool GetDirty() const
		{
			return mDirty;
		}
	};
}