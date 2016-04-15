#pragma once

#include "pch.h"
#include "Buffer.h"
#include "Entity.h"
#include "ArrayBuffer.h"

namespace Base
{
	using namespace Math;

	template<typename T>
	class DLL_EXPORT Mesh: public Buffer, public Entity
	{
	public :
		ObjTypePtr( Mesh );

		static Ptr Create( const std::string& name );

		static Ptr Create( const std::string& name, T* vertexData, uint32_t* indexData );

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