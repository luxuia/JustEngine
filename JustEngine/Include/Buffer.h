#pragma once

#include "Macros.h"

namespace JustEngine
{
	class DLL_EXPORT Buffer
	{
	protected:
		bool mDirty = true;
	public:
		virtual void DeleteBuffer();
		virtual bool UpdateBuffer();

		virtual void* GetBuffer();

		virtual UINT GetStride();
		virtual UINT GetOffset();

		bool GetDirty() const
		{
			return mDirty;
		}
	};
	inline void Buffer::DeleteBuffer() {}
	inline bool Buffer::UpdateBuffer()
	{
		return false;
	}
	inline void * Buffer::GetBuffer()
	{
		return NULL;
	}
	inline UINT Buffer::GetStride() { return 0; }
	inline UINT Buffer::GetOffset() { return 0; }
}