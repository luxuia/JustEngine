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
}