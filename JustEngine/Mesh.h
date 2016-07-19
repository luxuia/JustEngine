#pragma once

#include "pch.h"
#include "Buffer.h"
#include "Entity.h"
#include "ArrayBuffer.h"

namespace JustEngine
{
	using namespace Math;
	
	class DLL_EXPORT BaseMesh : public Entity
	{
	public:
		ObjTypePtr(BaseMesh);
		BaseMesh(const std::string& name) : Entity(name) {};

		virtual bool BindDraw(ID3D11DeviceContext* context) = 0;
	};


	template<typename T>
	class DLL_EXPORT Mesh: public BaseMesh
	{
	public :
		ObjTypePtr( Mesh<T> );

		Mesh(const std::string&, T*, int, uint32_t*, int);
		
		static Ptr Create( const std::string& name );

		static Ptr Create( const std::string& name, T* vertexData, int, uint32_t* indexData, int);

		ArrayBufferu IdxBuffer;
		ArrayBuffer<T> VertexBuffer;

		//D3D11_INPUT_ELEMENT_DESC* GetInputLayout() override;
		//int GetInputLayoutSize() override;
		bool BindDraw(ID3D11DeviceContext* context) override;

		const UINT STRIDE = sizeof(T);
		UINT Offset = 0;
	};

	////////////////////////////// Implement Start ///////////////////////////


	template <typename T>
	std::shared_ptr<Mesh<T>> Mesh<T>::Create(const std::string& name)
	{
		return std::make_shared< Mesh<T> >(name, nullptr, 0, nullptr, 0);
	}

	template <typename T>
	std::shared_ptr<Mesh<T>> Mesh<T>::Create(const std::string& name, T* vertexData, int vertexCnt,
		uint32_t* indexData, int indexCnt)
	{
		return std::make_shared< Mesh<T> >(name, vertexData, vertexCnt, indexData, indexCnt);
	}

	template <typename T>
	Mesh<T>::Mesh(const std::string& name, T* vertextData, int vertexCnt, uint32_t* indexData, int indexCnt) : BaseMesh(name)
	{
		if (vertextData != nullptr)
		{
			VertexBuffer = ArrayBuffer<T>(name, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER);
			VertexBuffer.SetupBuffer(vertextData, vertexCnt);
		}
		if (indexData != nullptr)
		{
			IdxBuffer = ArrayBufferu(name, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER);
			IdxBuffer.SetupBuffer(indexData, indexCnt);
		}
	}

	//template <typename T>
	//D3D11_INPUT_ELEMENT_DESC* Mesh<T>::GetInputLayout()
	//{
	//	return
	//	{ {
	//		"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA}, };
	//}
	//template <typename T>
	//int Mesh<T>::GetInputLayoutSize()
	//{
	//	return 1;
	//}

	template <typename T>
	bool Mesh<T>::BindDraw(ID3D11DeviceContext* context)
	{
		context->IASetVertexBuffers(0, 1, &VertexBuffer.pBuffer, &STRIDE, &Offset);
		context->IASetIndexBuffer(IdxBuffer.pBuffer, DXGI_FORMAT_R32_UINT, 0);

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		context->DrawIndexed(IdxBuffer.DataCount, 0, 0);

		return true;
	}
}