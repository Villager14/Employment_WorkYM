#include "GlitchNoise.hlsli"

Texture2D tex : register(t0);

SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//		テクスチャ
	float4 output = tex.Sample(samLinear, input.tex);



	return output;
}