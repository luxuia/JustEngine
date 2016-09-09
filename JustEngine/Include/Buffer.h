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
		virtual bool UpdateBuffer() = 0;

		virtual void* GetBuffer()  = 0;


		const UINT Stride = 0;
		const UINT Offset = 0;

		bool GetDirty() const
		{
			return mDirty;
		}
	};
}