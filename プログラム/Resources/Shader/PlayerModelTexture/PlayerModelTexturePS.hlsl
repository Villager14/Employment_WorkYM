#include "PlayerModelTexture.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//		Fî•ñ‚ğó‚¯æ‚é
	float4 output = tex.Sample(samLinear, input.tex);

	if (output.r + output.g + output.b >= 3.0f)
	{
		output.a = 0.0f;
	}

	return output;
}