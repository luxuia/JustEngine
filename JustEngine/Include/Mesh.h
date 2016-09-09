#pragma once

#include "pch.h"
#include "Buffer.h"
#include "Entity.h"
#include "ArrayBuffer.h"

namespace JustEngine
{

	class DLL_EXPORT Mesh: public Entity
	{
	public :
		ObjTypePtr( Mesh );

		Mesh(const std::string& name);
		
		static Ptr Create( const std::string& name );

		ArrayBufferu IdxBuffer;
		ArrayBufferf PositionBuffer;
		ArrayBufferf NormalBuffer;
		ArrayBufferf* pUVBuffers;
		ArrayBufferf ColorBuffer;

		void UpdateBuffer();

		//D3D11_INPUT_ELEMENT_DESC* GetInputLayout() override;
		//int GetInputLayoutSize() override;
		bool BindDraw(ID3D11DeviceContext* context);
	private:
		ID3D11Buffer** ppBuffers;
		UINT* pStrides;
		UINT* pOffsets;
		UINT BufferSize;
	};
}