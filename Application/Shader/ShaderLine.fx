
cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}

struct VS_Output
{
	float4 Pos: SV_POSITION;
	float4 Color: COLOR0;
};


//// Vertex Shader
VS_Output VS(float4 Pos: POSITION, float4 Color:COLOR)
{
	VS_Output output = (VS_Output)0;

	output.Pos = mul(World, Pos);
	output.Pos = mul(View, output.Pos);
	output.Pos = mul(Projection, output.Pos);

	output.Color = Color;
	return output;
}


// Pixel Shader
float4 PS(VS_Output input): SV_TARGET
{
	return input.Color;
}