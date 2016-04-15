#include "Mesh.h"

namespace Base
{
	template <typename T>
	Mesh::Ptr Mesh::Create( const std::string& name )
	{
		return std::make_shared< Mesh<T> >( name, nullptr, nullptr );
	}

	template <typename T>
	Mesh::Ptr Mesh::Create( const std::string& name, T* vertexData, uint32_t* indexData)
	{
		return std::make_shared< Mesh<T> >( name, vertexData, indexData );
	}

	template <typename T>
	Mesh::Mesh( const std::string& name, T* vertextData, uint32_t* indexData ) : Entity(name )
	{
		if (vertextData != nullptr)
		{
			VertexBuffer.SetupBuffer( vertextData );
		}
		if (indexData != nullptr)
		{
			IdxBuffer.SetupBuffer( indexData );
		}
	}
}