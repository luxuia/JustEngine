#include "pch.h"
#include "GameCore.h"
#include "GraphicsCore.h"

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if (x != nullptr) {x->Release(); x=nullptr;}
#endif

DXGI_FORMAT SpawnChainFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
DXGI_FORMAT OverlayPlaneFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

namespace GameCore
{
	extern HWND g_hWnd;
}

namespace Graphics
{
	uint32_t g_NativeWidth = 1920;
	uint32_t g_NativeHeight = 1080;

	uint32_t g_DisplayWidth = 1920;
	uint32_t g_DisplayHeight = 1080;

	enum eResolution { k720p, k900p, k1080p, k1440p, k2160p }; 

	float* BackGroundColor = new float[4]{ .0f, 0.3f, 0.7f, 1.f };

	ID3D11Device* g_Device = nullptr;

	D3D_FEATURE_LEVEL g_D3DFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	IDXGISwapChain* s_PrimarySwapChain = nullptr;
	ID3D11DeviceContext* s_PrimaryDeviceContext = nullptr;
	ID3D11RenderTargetView* s_PrimaryRenderTargetView = nullptr;

	D3D11_SAMPLER_DESC SamplerLinearWrapDesc;
	D3D11_SAMPLER_DESC SamplerAnisoWrapDesc;
	D3D11_SAMPLER_DESC SamplerShadowDesc;
	D3D11_SAMPLER_DESC SamplerLinearClampDesc;
	D3D11_SAMPLER_DESC SamplerVolumeWrapDesc;
	D3D11_SAMPLER_DESC SamplerPointClampDesc;
	D3D11_SAMPLER_DESC SamplerPointBorderDesc;
	D3D11_SAMPLER_DESC SamplerLinearBorderDesc;

	ID3D11SamplerState* SamplerLinearWrap = nullptr;
	ID3D11SamplerState* SamplerAnisoWrap = nullptr;
	ID3D11SamplerState* SamplerShadow = nullptr;
	ID3D11SamplerState* SamplerLinearClamp = nullptr;
	ID3D11SamplerState* SamplerVolumeWrap = nullptr;
	ID3D11SamplerState* SamplerPointClamp = nullptr;
	ID3D11SamplerState* SamplerPointBorder = nullptr;
	ID3D11SamplerState* SamplerLinearBorder = nullptr;

	D3D11_RASTERIZER_DESC RasterizerDefault;
	D3D11_RASTERIZER_DESC RasterizerDefaultCW;
	D3D11_RASTERIZER_DESC RasterizerTwoSided;
	D3D11_RASTERIZER_DESC RasterizerShadow;
	D3D11_RASTERIZER_DESC RasterizerShadowCW;

	ID3D11RasterizerState* RasterizerDefaultState = nullptr;

	D3D11_BLEND_DESC BlendNoColorWrite;
	D3D11_BLEND_DESC BlendDisable;
	D3D11_BLEND_DESC BlendPreMultiplied;
	D3D11_BLEND_DESC BlendTraditional;
	D3D11_BLEND_DESC BlendAdditive;
	D3D11_BLEND_DESC BlendTraditionalAdditive;
	
	ID3D11BlendState* BlendDisableState = nullptr;

	D3D11_DEPTH_STENCIL_DESC DepthStateDisabled;
	D3D11_DEPTH_STENCIL_DESC DepthStateReadWrite;
	D3D11_DEPTH_STENCIL_DESC DepthStateReadOnly;
	D3D11_DEPTH_STENCIL_DESC DepthStateReadOnlyReversed;
	D3D11_DEPTH_STENCIL_DESC DepthStateTestEqual;

	ID3D11DepthStencilState* DepthStateDisabledState = nullptr;
}

// Init DirtectX resource
void Graphics::Init( void )
{
	using namespace std;

	ASSERT( s_PrimarySwapChain == nullptr, "Graphic has already been initialized" );

	// init spawn chain and device
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT;
	sd.BufferDesc.Width = g_DisplayWidth;
	sd.BufferDesc.Height = g_DisplayHeight;
	sd.BufferDesc.Format = SpawnChainFormat;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.SampleDesc.Quality = 0; 
	sd.SampleDesc.Count = 1;

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	sd.OutputWindow = GameCore::g_hWnd;
	sd.Windowed = true;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (SUCCEEDED( D3D11CreateDeviceAndSwapChain( nullptr, USE_WRAP_DRIVER ? D3D_DRIVER_TYPE_HARDWARE:D3D_DRIVER_TYPE_WARP, 
			nullptr, 0, &g_D3DFeatureLevel, 1, D3D11_SDK_VERSION, &sd, &s_PrimarySwapChain, &g_Device, nullptr, &s_PrimaryDeviceContext ) ))
	{
		Utility::Printf( L"D3D11 hardware found" );

		ID3D11Texture2D* pBackBuffer;
		s_PrimarySwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer );

		g_Device->CreateRenderTargetView( pBackBuffer, nullptr, &s_PrimaryRenderTargetView );

		s_PrimaryDeviceContext->OMSetRenderTargets( 1, &s_PrimaryRenderTargetView, nullptr );

		D3D11_VIEWPORT vp;
		vp.Width = (float)g_DisplayWidth;
		vp.Height = (float)g_DisplayHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		s_PrimaryDeviceContext->RSSetViewports( 1, &vp );
	}
	else
	{
	}

	SamplerLinearWrapDesc = {};
	SamplerLinearWrapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_Device->CreateSamplerState( &SamplerLinearWrapDesc, &SamplerLinearWrap );
	SetDebugName( SamplerLinearWrap, "SamplerLinearWrap" );

	SamplerAnisoWrapDesc.MaxAnisotropy = 8;
	g_Device->CreateSamplerState( &SamplerAnisoWrapDesc, &SamplerAnisoWrap );
	SetDebugName( SamplerLinearWrap, "SamplerLinearWrap" );

	SamplerShadowDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	SamplerShadowDesc.ComparisonFunc = D3D11_COMPARISON_GREATER_EQUAL;
	SamplerShadowDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerShadowDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerShadowDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	g_Device->CreateSamplerState( &SamplerShadowDesc, &SamplerShadow );
	SetDebugName( SamplerLinearWrap, "SamplerLinearWrap" );

	SamplerLinearClampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_Device->CreateSamplerState( &SamplerLinearClampDesc, &SamplerLinearClamp );
	SetDebugName( SamplerLinearWrap, "SamplerLinearClamp" );

	SamplerPointClampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	g_Device->CreateSamplerState( &SamplerPointClampDesc, &SamplerPointClamp );
	SetDebugName( SamplerLinearWrap, "SamplerPointClamp" );

	SamplerVolumeWrapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	SamplerVolumeWrapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerVolumeWrapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerVolumeWrapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	g_Device->CreateSamplerState( &SamplerVolumeWrapDesc, &SamplerVolumeWrap );
	SetDebugName( SamplerLinearWrap, "SamplerVolumeWrap" );

	SamplerLinearBorderDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerLinearBorderDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	g_Device->CreateSamplerState( &SamplerLinearBorderDesc, &SamplerLinearBorder );
	SetDebugName( SamplerLinearWrap, "SamplerLinearBorder" );

	SamplerPointBorderDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	g_Device->CreateSamplerState( &SamplerPointBorderDesc, &SamplerPointBorder );
	SetDebugName( SamplerLinearWrap, "SamplerPointBorder" );

	// Default rasterizer states
	RasterizerDefault.FillMode = D3D11_FILL_SOLID;
	RasterizerDefault.CullMode = D3D11_CULL_BACK;
	RasterizerDefault.FrontCounterClockwise = TRUE;
	RasterizerDefault.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
	RasterizerDefault.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
	RasterizerDefault.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	RasterizerDefault.DepthClipEnable = TRUE;
	RasterizerDefault.MultisampleEnable = FALSE;
	RasterizerDefault.AntialiasedLineEnable = FALSE;

	g_Device->CreateRasterizerState( &RasterizerDefault, &RasterizerDefaultState );
	SetDebugName( SamplerLinearWrap, "RasterizerDefaultState" );

	RasterizerDefaultCW = RasterizerDefault;
	RasterizerDefaultCW.FrontCounterClockwise = FALSE;

	RasterizerTwoSided = RasterizerDefault;
	RasterizerTwoSided.CullMode = D3D11_CULL_NONE;

	// Shadows need their own rasterizer state so we can reverse the winding of faces
	RasterizerShadow = RasterizerDefault;
	//RasterizerShadow.CullMode = D3D12_CULL_FRONT;  // Hacked here rather than fixing the content
	RasterizerShadow.SlopeScaledDepthBias = -1.5f;
	RasterizerShadow.DepthBias = -100;

	RasterizerShadowCW = RasterizerShadow;
	RasterizerShadowCW.FrontCounterClockwise = FALSE;

	DepthStateDisabled.DepthEnable = FALSE;
	DepthStateDisabled.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	DepthStateDisabled.DepthFunc = D3D11_COMPARISON_ALWAYS;
	DepthStateDisabled.StencilEnable = FALSE;
	DepthStateDisabled.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	DepthStateDisabled.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	DepthStateDisabled.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	DepthStateDisabled.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStateDisabled.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStateDisabled.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStateDisabled.BackFace = DepthStateDisabled.FrontFace;
	g_Device->CreateDepthStencilState( &DepthStateDisabled, &DepthStateDisabledState );
	SetDebugName( SamplerLinearWrap, "DepthStateDisabledState" );
	DepthStateReadWrite = DepthStateDisabled;
	DepthStateReadWrite.DepthEnable = TRUE;
	DepthStateReadWrite.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStateReadWrite.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;

	DepthStateReadOnly = DepthStateReadWrite;
	DepthStateReadOnly.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	DepthStateReadOnlyReversed = DepthStateReadOnly;
	DepthStateReadOnlyReversed.DepthFunc = D3D11_COMPARISON_LESS;

	DepthStateTestEqual = DepthStateReadOnly;
	DepthStateTestEqual.DepthFunc = D3D11_COMPARISON_EQUAL;

	D3D11_BLEND_DESC alphaBlend = {};
	alphaBlend.IndependentBlendEnable = FALSE;
	alphaBlend.RenderTarget[0].BlendEnable = FALSE;
	alphaBlend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	alphaBlend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	alphaBlend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	alphaBlend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	alphaBlend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	alphaBlend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	alphaBlend.RenderTarget[0].RenderTargetWriteMask = 0;
	BlendNoColorWrite = alphaBlend;

	alphaBlend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	BlendDisable = alphaBlend;
	g_Device->CreateBlendState( &BlendDisable, &BlendDisableState );
	SetDebugName( SamplerLinearWrap, "BlendDisableState" );

	alphaBlend.RenderTarget[0].BlendEnable = TRUE;
	BlendTraditional = alphaBlend;

	alphaBlend.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	BlendPreMultiplied = alphaBlend;

	alphaBlend.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	BlendAdditive = alphaBlend;

	alphaBlend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendTraditionalAdditive = alphaBlend;

#if _DEBUG 
	shared_ptr<ID3D11Debug> debugInterface;
#endif
}


void Graphics::CleanUp()
{
	SAFE_RELEASE(g_Device);
}

void Graphics::Resize( uint32_t width, uint32_t height )
{
	ASSERT( s_PrimarySwapChain != nullptr );

	g_DisplayHeight = height;
	g_DisplayWidth = width;

	DEBUGPRINT( "Changing display resolution to %ux%u", width, height );

	s_PrimarySwapChain->ResizeBuffers( SWAP_CHAIN_BUFFER_COUNT, width, height, SpawnChainFormat, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH );

}

void Graphics::Terminate()
{
	
}

void Graphics::Present()
{
	ASSERT( s_PrimaryDeviceContext != nullptr );

	s_PrimarySwapChain->Present(4, 0);


	s_PrimaryDeviceContext->ClearRenderTargetView(s_PrimaryRenderTargetView, BackGroundColor);
}

uint64_t Graphics::GetFrameCount(void)
{
	return uint64_t();
}
