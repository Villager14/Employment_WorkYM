#include "CenterShader.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	float a =  distance(input.tex.y, 0.5f);

	float b = lerp(0.5f, 0.0f, time.x);

	float c = input.tex.y - b;

	output.a *= ceil(c);
	
	float d = lerp(0.5f, 1.0f, time.x);

	float e = input.tex.y - d;

	output.a *= floor(e) * -1.0f;

	return output;
}