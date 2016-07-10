#include "Mesh.h"
#include "ClassConfig.h"

namespace JustEngine
{
	template <typename T>
	std::shared_ptr<Mesh<T>> Mesh<T>::Create( const std::string& name )
	{
		return std::make_shared< Mesh<T> >( name, nullptr, 0, nullptr, 0);
	}

	template <typename T>
	std::shared_ptr<Mesh<T>> Mesh<T>::Create( const std::string& name, T* vertexData, int vertexCnt, 
			uint32_t* indexData, int indexCnt)
	{
		return std::make_shared< Mesh<T> >( name, vertexData, vertexCnt, indexData, indexCnt);
	}

	template <typename T>
	Mesh<T>::Mesh( const std::string& name, T* vertextData, int vertexCnt, uint32_t* indexData, int indexCnt) : BaseMesh(name )
	{
		if (vertextData != nullptr)
		{
			VertexBuffer = ArrayBuffer<T>(name, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER);
			VertexBuffer.SetupBuffer( vertextData, vertexCnt);
		}
		if (indexData != nullptr)
		{
			IdxBuffer = ArrayBufferu(name, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER);
			IdxBuffer.SetupBuffer( indexData, indexCnt);
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
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		context->Draw(VertexBuffer.DataCount, 0);

		return true;
	}

	template DLL_EXPORT class Mesh<MeshP3>;
	template DLL_EXPORT class Mesh<MeshP3N3>;
	template DLL_EXPORT class Mesh<MeshP3N3U2>;

}