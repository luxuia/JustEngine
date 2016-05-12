#pragma once

#include "pch.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

namespace Graphics
{
	using namespace Microsoft::WRL;

	void Init( void );
	void Resize( uint32_t width, uint32_t height );
	void Terminate( void );
	void CleanUp( void );
	void Present( void );

	extern uint32_t g_DisplayWidth;
	extern uint32_t g_DisplayHeight;

	uint64_t GetFrameCount( void );

	extern std::shared_ptr<ID3D11Device> g_Device;
	extern D3D_FEATURE_LEVEL g_D3DFertureLevel;

	extern D3D11_SAMPLER_DESC SamplerLinearWrapDesc;
	extern D3D11_SAMPLER_DESC SamplerAnisoWrapDesc;
	extern D3D11_SAMPLER_DESC SamplerShadowDesc;
	extern D3D11_SAMPLER_DESC SamplerLinearClampDesc;
	extern D3D11_SAMPLER_DESC SamplerVolumeWrapDesc;
	extern D3D11_SAMPLER_DESC SamplerPointClampDesc;
	extern D3D11_SAMPLER_DESC SamplerPointBorderDesc;
	extern D3D11_SAMPLER_DESC SamplerLinearBorderDesc;

	extern D3D11_RASTERIZER_DESC RasterizerDefault;
	extern D3D11_RASTERIZER_DESC RasterizerDefaultCW;
	extern D3D11_RASTERIZER_DESC RasterizerTwoSided;
	extern D3D11_RASTERIZER_DESC RasterizerShadow;
	extern D3D11_RASTERIZER_DESC RasterizerShadowCW;

	extern D3D11_BLEND_DESC BlendNoColorWrite;		//XXX
	extern D3D11_BLEND_DESC BlendDisable;			// 1, 0
	extern D3D11_BLEND_DESC BlendPreMultiplied;		// 1, 1-SrcA
	extern D3D11_BLEND_DESC BlendTraditional;		// SrcA, 1-SrcA
	extern D3D11_BLEND_DESC BlendAdditive;			// 1, 1
	extern D3D11_BLEND_DESC BlendTraditionalAdditive;// SrcA, 1

	extern D3D11_DEPTH_STENCIL_DESC DepthStateDisabled;
	extern D3D11_DEPTH_STENCIL_DESC DepthStateReadWrite;
	extern D3D11_DEPTH_STENCIL_DESC DepthStateReadOnly;
	extern D3D11_DEPTH_STENCIL_DESC DepthStateReadOnlyReversed;
	extern D3D11_DEPTH_STENCIL_DESC DepthStateTestEqual;

#if defined(PROFILE) || defined(_DEBUG)
	inline void SetDebugName( ID3D11Device* pObj, const CHAR* pstrName )
	{
		if (pObj)
			pObj->SetPrivateData( WKPDID_D3DDebugObjectName, lstrlenA( pstrName ), pstrName );
	}
	inline void SetDebugName( ID3D11DeviceChild* pObj, const CHAR* pstrName )
	{
		if (pObj)
			pObj->SetPrivateData( WKPDID_D3DDebugObjectName, lstrlenA( pstrName ), pstrName );
	}
#else
#define DXUT_SetDebugName( pObj, pstrName )
#endif
}