#include "UIShader.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	//output.a *= lerp(1.0f, 0.0f, step(input.color.x, input.tex.x));

	//return float4(output.r, output.r, output.r, output.a);

	//return float4(output.r, output.r, output.r, output.a);

	//float depthValu = tex.Sample(samLinear, input.tex).r;

	//return float4(depthValu, depthValu, depthValu, output.a);

	return output;
}