#pragma once

#include "pch.h"
#include "Buffer.h"

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
	typedef ArrayBuffer<int> ArrayBufferi;
	typedef ArrayBuffer<float> ArrayBufferf;
	typedef ArrayBuffer<uint32_t> ArrayBufferu;
}