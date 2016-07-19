#include "Shader.h"
#include "d3dcompiler.h"
#include "GraphicsCore.h"

namespace JustEngine
{
	using namespace Graphics;

	Shader::Ptr Shader::Create( const std::string& path, const std::string& entryPoint, const std::string& shaderModel)
	{
		return std::make_shared<Shader>(path, entryPoint, shaderModel );
	}

	Shader::Shader( const std::string& path, const std::string& entryPoint, const std::string& shaderModel ) :Entity(path )
	{
		mFilePath = path;

		ID3DBlob* pBlob;
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(_DEBUG) || defined(DEBUG)
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		shaderFlags |= D3DCOMPILE_DEBUG;
#endif
		ID3DBlob* errBlob;
		HRESULT hr = D3DX11CompileFromFileA( path.c_str(), nullptr, nullptr, Shader::SHADER_MAIN_VERTEX, ("vs"+shaderModel).c_str(),
			shaderFlags, 0, nullptr, &pBlob, &errBlob, nullptr );
		if (FAILED( hr ))
		{
			if (errBlob != nullptr)
			{
				OutputDebugStringA( (char*)errBlob->GetBufferPointer() );
				errBlob->Release();
			}
			return;
		}

		g_Device->CreateVertexShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader );
		
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT numElement = ARRAYSIZE(layout);

		hr = g_Device->CreateInputLayout(layout, numElement, pBlob->GetBufferPointer(),
									pBlob->GetBufferSize(), &pInputLayout);
		
		pBlob->Release();

		hr = D3DX11CompileFromFileA( path.c_str(), nullptr, nullptr, Shader::SHADER_MAIN_PIXEL, ("ps"+shaderModel).c_str(),
			shaderFlags, 0, nullptr, &pBlob, &errBlob, nullptr);
		if (FAILED( hr ))
		{
			if (errBlob != nullptr)
			{
				OutputDebugStringA( (char*)errBlob->GetBufferPointer() );
				errBlob->Release();
			}
			return;
		}
		g_Device->CreatePixelShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader );
		pBlob->Release();

		mIsDirty = false;
	}

	template<typename T>
	void Shader::VSAppendConstantBuffer()
	{
		D3D11_BUFFER_DESC db = {};
		db.Usage = D3D11_USAGE_DEFAULT;
		db.ByteWidth = sizeof(T);
		db.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		db.CPUAccessFlags = 0;

		ID3D11Buffer* buffer;
		g_Device->CreateBuffer( &db, nullptr, &buffer );
		VertexBuffer.push_back( buffer );
	}

	template<typename T>
	void Shader::PSAppendConstantBuffer( )
	{
		D3D11_BUFFER_DESC db = {};
		db.Usage = D3D11_USAGE_DEFAULT;
		db.ByteWidth = sizeof(T);
		db.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		db.CPUAccessFlags = 0;

		ID3D11Buffer* buffer;
		g_Device->CreateBuffer( &db, nullptr, &buffer );
		PixelBuffer.push_back( buffer );
	}

	template<typename T> 
	void Shader::VSUpdateConstantBuffer(ID3D11DeviceContext* context, T* constantBuffer, int slotIdx )
	{
		ASSERT( slotIdx < VertexBuffer.size() );

		context->UpdateSubresource( VertexBuffer[slotIdx], 0, nullptr, constantBuffer, 0, 0 );
	}

	template<typename T>
	void Shader::PSUpdateConstantBuffer(ID3D11DeviceContext* context, T* constantBuffer, int slotIdx )
	{
		ASSERT( slotIdx < PixelBuffer.size() );

		context->UpdateSubresource( PixelBuffer[slotIdx], 0, nullptr, constantBuffer, 0, 0 );
	}
}