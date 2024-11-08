#include "AboveUI.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 uv = input.tex;

	uv.y -= 1.0f;
	uv.y += clamp(time.x, 0.0f, 1.0f);

	float4 output = tex.Sample(samLinear, uv);

	output.w *= ceil(uv.y);


	return output;
}