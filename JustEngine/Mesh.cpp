#include "Mesh.h"

namespace Base
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
	Mesh<T>::Mesh( const std::string& name, T* vertextData, int vertexCnt, uint32_t* indexData, int indexCnt) : Entity(name )
	{
		if (vertextData != nullptr)
		{
			VertexBuffer.SetupBuffer( vertextData, vertexCnt);
		}
		if (indexData != nullptr)
		{
			IdxBuffer.SetupBuffer( indexData, indexCnt);
		}
	}

	template<typename T>
	void Mesh<T>::DeleteBuffer()
	{

	}

	template DLL_EXPORT class Mesh<MeshP3>;
	template DLL_EXPORT class Mesh<MeshP3N3>;
	template DLL_EXPORT class Mesh<MeshP3N3U2>;
}