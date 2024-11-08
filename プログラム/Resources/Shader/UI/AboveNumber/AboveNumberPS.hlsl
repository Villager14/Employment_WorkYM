#include "AboveNumber.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 uv = input.tex;

	uv.x /= 10.0f;

	uv.x += 1.0f / 10.0f * number.x;

	uv.y += time.x;

	float4 output = tex.Sample(samLinear, uv);

	output.w *= floor(uv.y);

	return output;
}