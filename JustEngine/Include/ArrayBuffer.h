#pragma once

#include "pch.h"
#include "Buffer.h"
#include "GraphicsCore.h"
#include "Vector.h"
#include <vector>

namespace JustEngine
{
	template<class T>
	class ArrayBuffer : public Buffer
	{
	public:
		ArrayBuffer( const std::string& name, D3D11_USAGE buff_usage, D3D11_BIND_FLAG bind_flag );
		ArrayBuffer() = default;
		std::vector<T> Data;

		virtual bool UpdateBuffer() override;

		void Bind( ID3D11DeviceContext* context );

		virtual void DeleteBuffer() override;

		virtual void* GetBuffer();

		virtual UINT GetStride();
		virtual UINT GetOffset();
		
		const UINT Stride = sizeof(T);
		UINT Offset = 0;
		
		ID3D11Buffer* pBuffer;
	protected:
		D3D11_USAGE mUsage;

		D3D11_BIND_FLAG mBindFlag;

	};

	template<class T>
	UINT JustEngine::ArrayBuffer<T>::GetOffset()
	{
		return Offset;
	}

	template<class T>
	UINT JustEngine::ArrayBuffer<T>::GetStride()
	{
		return Stride;
	}

	template<class T>
	ArrayBuffer<T>::ArrayBuffer(const std::string& name, D3D11_USAGE buff_usage, D3D11_BIND_FLAG bind_flag)
	{
		mUsage = buff_usage;
		mBindFlag = bind_flag;
	}

	template<class T>
	void ArrayBuffer<T>::DeleteBuffer()
	{
	}

	template<class T>
	bool ArrayBuffer<T>::UpdateBuffer()
	{
		if (Data.size() == 0) return false;

		D3D11_BUFFER_DESC db = {};
		db.Usage = mUsage;
		db.ByteWidth = sizeof(T)*Data.size();
		db.BindFlags = mBindFlag;
		db.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = &(*Data.begin());
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
	typedef ArrayBuffer<Vector3> ArrayBufferV3;
	typedef ArrayBuffer<Vector4> ArrayBufferV4;
}