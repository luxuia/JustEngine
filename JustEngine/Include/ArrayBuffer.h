#pragma once

#include "pch.h"
#include "Buffer.h"
#include "GraphicsCore.h"

namespace JustEngine
{
	template<class T>
	class ArrayBuffer : public Buffer
	{
	public:
		ArrayBuffer( const std::string& name, D3D11_USAGE buff_usage, D3D11_BIND_FLAG bind_flag );
		ArrayBuffer() = default;
		T* Data = nullptr;

		int DataCount = 0;

		bool UpdateBuffer() override;

		void Bind( ID3D11DeviceContext* context );

		virtual void DeleteBuffer() override;

		void* GetBuffer();

		const UINT Stride = sizeof(T);

		ID3D11Buffer* pBuffer;
	protected:
		D3D11_USAGE mUsage;

		D3D11_BIND_FLAG mBindFlag;

	};

	template<class T>
	ArrayBuffer<T>::ArrayBuffer(const std::string& name, D3D11_USAGE buff_usage, D3D11_BIND_FLAG bind_flag)
	{
		mUsage = buff_usage;
		mBindFlag = bind_flag;
	}

	template<class T>
	void ArrayBuffer<T>::DeleteBuffer()
	{
		if (Data != nullptr)
		{
			delete Data;
		}
	}

	template<class T>
	bool ArrayBuffer<T>::UpdateBuffer()
	{
		if (Data == nullptr) return false;

		D3D11_BUFFER_DESC db = {};
		db.Usage = mUsage;
		db.ByteWidth = sizeof(T)*DataCount;
		db.BindFlags = mBindFlag;
		db.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = Data;
		HRESULT hr = Graphics::g_Device->CreateBuffer(&db, &InitData, &pBuffer);
		if (FAILED(hr))
		{
			//log
			return false;
		}
		return true;
	}

	template<class T>
	void* ArrayBuffer<T>::GetBuffer()
	{
		return pBuffer;
	}

	template< class T>
	void ArrayBuffer<T>::Bind(ID3D11DeviceContext* context)
	{

	}
	
	typedef ArrayBuffer<int> ArrayBufferi;
	typedef ArrayBuffer<float> ArrayBufferf;
	typedef ArrayBuffer<uint32_t> ArrayBufferu;
}