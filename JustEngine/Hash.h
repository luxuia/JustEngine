#pragma once

namespace Utility
{
	inline size_t HashIterate( size_t next, size_t current_hash = 2166136261U )
	{
		return 16777619U * current_hash ^ next;
	}

	// Warning, Type mush size_t aligned
	template <typename T> inline size_t HashRange( const T* begin, const T* end, size_t init_hash = 2166136261U )
	{
		static_assert((sizeof(T)& 3) == 0, "hashArray Type Not Word-Aligned");
		while (begin < end)
		{
			init_hash = HashIterate( (size_t)*begin++, init_hash );
		}
		return init_hash;
	}

	template <typename T> inline size_t HashArray( const T* begin, size_t count, size_t init_hash = 2166136261U )
	{
		static_assert((sizeof(T)& 3) == 0, "hashArray Type Not Word-Aligned");
		return HashRange( begin, (size_t*)(begin + count), init_hash );
	}

	template<typename T> inline size_t Hash( const T* begin, size_t init_hash = = 2166136261U )
	{
		static_assert((sizeof(T)& 3) == 0, "hashArray Type Not Word-Aligned");
		return HashRange( (size_t*)begin, (size_t*)(begin + 1), init_hash );
	}
}