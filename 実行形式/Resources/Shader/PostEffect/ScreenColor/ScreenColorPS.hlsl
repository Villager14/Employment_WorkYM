#include "ScreenColor.hlsli"

Texture2D tex : register(t0);

SamplerState samLinear : register(s0);

inline float Gray(float4 color)
{
	return color.r * 0.3f + color.g * 0.6f + color.b * 0.1f;
}

float4 Sepia(float4 color)
{
	float r = screenColor.x;
	float g = screenColor.y;
	float b = screenColor.z;


	float all = (r + g + b);

	float gray = Gray(color);

	return float4(gray * (r / all * 3), gray * (g / all * 3), gray * (b / all * 3), color.a);
}

float4 main(PS_INPUT input) : SV_TARGET
{
	//		テクスチャ
	float4 output = tex.Sample(samLinear, input.tex);

	//		セピア
	float4 sepiaVal = Sepia(output);

	//		時間経過により色を変える
	output.r = lerp(output.r, sepiaVal.x, elapsedTime);
	output.g = lerp(output.g, sepiaVal.y, elapsedTime);
	output.b = lerp(output.b, sepiaVal.z, elapsedTime);

	return output;
}