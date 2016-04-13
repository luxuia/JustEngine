#pragma once

#include "pch.h"

namespace Base
{
	template<class T>
	class Singleton
	{
	protected:
		static std::shared_ptr<T> mInstance;

	public:
		static std::shared_ptr<T> &Instance()
		{
			if (mInstance == nullptr)
			{
				mInstance = std::make_shared<T>();
			}
			return mInstance;
		}

		static void Destroy()
		{
			if (mInstance != nullptr)
			{
				mInstance->DoDestroy();
			}
		}

		void DoDestroy()
		{

		}

		virtual ~Singleton()
		{
			mInstance = nullptr;
		}
	};

	template<class T>
	std::shared_ptr<T> Singleton<T>::mInstance = nullptr;
}