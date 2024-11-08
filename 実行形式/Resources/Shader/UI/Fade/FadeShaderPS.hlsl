#include "FadeShader.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	//output.a *= lerp(0.0f, 1.0f, time.x);

	output = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), output, time.x);

	return output;
}