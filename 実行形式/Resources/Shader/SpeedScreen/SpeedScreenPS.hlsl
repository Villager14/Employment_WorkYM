#include "SpeedScreen.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float Gray(float4 color)
{
	return color.r * 0.3f + color.g * 0.6f + color.b * 0.1f;
}

float4 Sepia(float4 color)
{
	float r = 255;
	float g = 0;
	float b = 0;

	float all = (r + g + b);

	float gray = Gray(color);

	return float4(gray * (r / all * 3), gray * (g / all * 3), gray * (b / all * 3), color.a);
}

float random(float2 uv)
{
	return frac(sin(dot(uv, float2(12.9898, 78.223))) * 43758.5453f);
}

float4 main(PS_INPUT input) : SV_TARGET
{
	//		Fî•ñ‚ğó‚¯æ‚é
	float4 output = tex.Sample(samLinear, input.tex);

	


	return output;
}