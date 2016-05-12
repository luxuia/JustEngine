#include "ArrayBuffer.h"
#include "GraphicsCore.h"

namespace Graphics
{
	template<class T>
	ArrayBuffer<T>::ArrayBuffer( const std::string& name, D3D11_USAGE buff_usage, D3D11_BIND_FLAG bind_flag )
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
	void ArrayBuffer<T>::SetupBuffer( T* data, int dataCount)
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
		
		HRESULT hr = g_Device->CreateBuffer( &db, &InitData, &pBuffer );
		if (FAILED( hr ))
		{
			//log
		}
	}

	template< class T> 
	void ArrayBuffer<T>::Bind(ID3D11DeviceContext* context)
	{

	}

	template class ArrayBuffer<int>;
	template class ArrayBuffer<float>;
	template class ArrayBuffer<uint32_t>;
}