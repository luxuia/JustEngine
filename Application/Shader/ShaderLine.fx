

//// Vertex Shader
float4 VS(float4 Pos: POSITION) : SV_POSITION
{
	return Pos;
}


// Pixel Shader
float4 PS(float4 Pos: SV_POSITION): SV_TARGET
{
	return float4(0.0f, 1.0f, 1.0, 1.0f);
}