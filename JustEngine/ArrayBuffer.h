#pragma once

#include "pch.h"
#include "Buffer.h"

namespace Graphics
{
	template<class T>
	class ArrayBuffer : public Base::Buffer
	{
	public:
		ArrayBuffer( const std::string& name, D3D11_USAGE buff_usage, D3D11_BIND_FLAG bind_flag );
		ArrayBuffer() = default;
		T* Data;

		int DataCount;

		void SetupBuffer(T* data, int count);

		void Bind( ID3D11DeviceContext* context );

		virtual void DeleteBuffer() override;

	protected:
		D3D11_USAGE mUsage;

		D3D11_BIND_FLAG mBindFlag;

		ID3D11Buffer* pBuffer;
	};
	typedef ArrayBuffer<int> ArrayBufferi;
	typedef ArrayBuffer<float> ArrayBufferf;
	typedef ArrayBuffer<uint32_t> ArrayBufferu;
}