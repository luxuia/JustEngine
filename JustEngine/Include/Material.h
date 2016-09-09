#pragma once

#include "Macros.h"
#include "Shader.h"
#include "Utility.h"

namespace JustEngine
{
	class DLL_EXPORT Material
	{
		friend class MeshRender;
	public:
		//template<typename T> void DeclareData( T data );
		//template<typename T> void SetData( T data);

		ObjTypePtr( Material );
		static Ptr Create();

		Material();

		ID3D11VertexShader* GetVertexShader();
		ID3D11PixelShader* GetPixelShadow();
		ID3D11InputLayout* GetInputLayout();

		bool Bind(ID3D11DeviceContext* context);

	protected:
		std::shared_ptr<Shader> mShader;
		// Texture::Ptr mTexture;
	};
}