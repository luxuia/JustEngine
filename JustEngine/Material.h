#pragma once

#include "Macros.h"
#include "Shader.h"
#include "Utility.h"

namespace Graphics
{
	class DLL_EXPORT Material
	{
	public:
		//template<typename T> void DeclareData( T data );
		//template<typename T> void SetData( T data);

		ObjTypePtr( Material );
		static Ptr Create();

		Material();

	protected:
		Shader::Ptr mShader;
		// Texture::Ptr mTexture;
	};
}