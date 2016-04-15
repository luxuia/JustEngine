#pragma once

#include "Macros.h"
#include "Shader.h"

namespace Graphics
{
	class DLL_EXPORT Material
	{
	public:
		//template<typename T> void DeclareData( T data );
		//template<typename T> void SetData( T data);

		ObjTypePtr( Material );


	protected:
		Shader::Ptr mShader;
		// Texture::Ptr mTexture;
	};
}