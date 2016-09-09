#pragma once

#include "pch.h"
#include "Entity.h"
#include "Serializable.h"

namespace JustEngine
{
	class DLL_EXPORT Shader : public Entity, public Serializable
	{
		friend class Material;

	public:
		ObjTypePtr( Shader );

		static Ptr Create(const std::string& path, const std::string& entryPoint, const std::string& shaderModel);

		Shader( const std::string& path, const std::string& entryPoint, const std::string& shaderModel );

		static constexpr const char* SHADER_MAIN_VERTEX = "VS";
		static constexpr const char* SHADER_MAIN_PIXEL = "PS";

		template<typename T> void VSAppendConstantBuffer( /*int slot*/);
		template<typename T> void PSAppendConstantBuffer( /*int slot*/);

		template<typename T> void VSUpdateConstantBuffer( ID3D11DeviceContext* context, T* constantBuffer, int slotIdx );
		template<typename T> void PSUpdateConstantBuffer( ID3D11DeviceContext* context, T* constantBuffer, int slotIdx );

	protected:
		std::string mFilePath;

		std::vector<ID3D11Buffer*> VertexBuffer;
		std::vector<ID3D11Buffer*> PixelBuffer;

		ID3D11InputLayout* pInputLayout;

		ID3D11VertexShader* pVertexShader;
		ID3D11PixelShader* pPixelShader;

		bool mIsDirty = true;
	};

}