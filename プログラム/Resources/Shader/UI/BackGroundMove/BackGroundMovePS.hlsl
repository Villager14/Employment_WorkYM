#include "BackGroundMove.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//float4 output = tex.Sample(samLinear, input.tex);

	float2 uv = input.tex;

	uv.x += time.x;

	return tex.Sample(samLinear, uv);
}