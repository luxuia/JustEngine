#include "Material.h"

namespace Graphics
{
	Material::Ptr Material::Create()
	{
		return std::make_shared<Material>();
	}

	Material::Material() 
	{

	}
}