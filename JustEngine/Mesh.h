#pragma once

#include "pch.h"
#include "Buffer.h"
#include "Entity.h"
#include "ArrayBuffer.h"

namespace Base
{
	using namespace Math;

	template<typename T>
	class Mesh: public Buffer, public Entity
	{
	public :
		ObjTypePtr( Mesh<T> );

		Mesh(const std::string&, T*, int, uint32_t*, int);
		
		static Ptr Create( const std::string& name );

		static Ptr Create( const std::string& name, T* vertexData, int, uint32_t* indexData, int);

		void DeleteBuffer() override;

		Graphics::ArrayBufferu IdxBuffer;
		Graphics::ArrayBuffer<T> VertexBuffer;
	};

	struct MeshP3
	{
		Vector3 Position;
	};

	struct MeshP3N3
	{
		Vector3 Position;
		Vector3 Normal;
	};

	struct MeshP3N3U2
	{
		Vector3 Position;
		Vector3 Normal;
		Vector2 UV;
	};
}