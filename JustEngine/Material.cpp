#include "Material.h"

namespace JustEngine
{
	Material::Ptr Material::Create()
	{
		return std::make_shared<Material>();
	}

	Material::Material() 
	{
		std::string filename = "Shader/ShaderLine.fx";
		std::string entrance = "";
		std::string version = "_4_0";
		mShader = Shader::Create(filename, entrance, version);
	}
	ID3D11VertexShader * Material::GetVertexShader()
	{
		return mShader->pVertexShader;
	}
	ID3D11PixelShader * Material::GetPixelShadow()
	{
		return mShader->pPixelShader;
	}
	ID3D11InputLayout* Material::GetInputLayout()
	{
		return mShader->pInputLayout;
	}

	bool Material::Bind(ID3D11DeviceContext* context)
	{
		context->IASetInputLayout(mShader->pInputLayout);
		context->VSSetShader(mShader->pVertexShader, nullptr, 0);
		context->PSSetShader(mShader->pPixelShader, nullptr, 0);

		return true;
	}
}