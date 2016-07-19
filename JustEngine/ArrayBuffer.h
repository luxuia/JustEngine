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

		void SetupBuffer(T* data, int count);

		void Bind( ID3D11DeviceContext* context );

		virtual void DeleteBuffer() override;

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
	void ArrayBuffer<T>::SetupBuffer(T* data, int dataCount)
	{
		DeleteBuffer();

		Data = data;
		DataCount = dataCount;

		D3D11_BUFFER_DESC db = {};
		db.Usage = mUsage;
		db.ByteWidth = sizeof(T)*dataCount;
		db.BindFlags = mBindFlag;
		db.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = data;
		HRESULT hr = Graphics::g_Device->CreateBuffer(&db, &InitData, &pBuffer);
		if (FAILED(hr))
		{
			//log
		}
	}

	template< class T>
	void ArrayBuffer<T>::Bind(ID3D11DeviceContext* context)
	{

	}
	
	typedef ArrayBuffer<int> ArrayBufferi;
	typedef ArrayBuffer<float> ArrayBufferf;
	typedef ArrayBuffer<uint32_t> ArrayBufferu;
}