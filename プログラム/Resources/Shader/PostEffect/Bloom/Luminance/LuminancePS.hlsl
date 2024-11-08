#include "Luminance.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	float t = dot(output.rgb, float3(0.2125f, 0.7154f, 0.721f));

	clip(t - 1.0f);

	return output;
}