#include "MenuSelect.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float move(float uv, float timeval, float length)
{
	float a = floor(lerp(0.0f - length, 1.0f, timeval) - uv) * -1.0f;
	float b = ceil(lerp(0.0f, 1.0f + length, timeval) - uv);

	return b * a;
}

float4 Process(float2 uv, float timeval, float4 output)
{
	float chack = ceil(timeval - 1.0f) * -1.0f + 1.0f;

	//		上のエフェクト
	output.w *= lerp(lerp(0.0f, move(uv.x, timeval, 0.1f), chack), 1.0f, ceil(uv.y - 0.05f));

	//		下のエフェクト
	output.w *= lerp(lerp(0.0f, move(uv.x, 1.0f - timeval, 0.1f), chack), 1.0f, floor(uv.y - (1.0f - 0.05f)) * -1.0f);

	//		左のエフェクト
	output.w *= lerp(lerp(move(uv.y, 2.0f - timeval, 0.3f), 0.0f, chack), 1.0f, ceil(uv.x - 0.05f));

	//		右のエフェクト
	output.w *= lerp(lerp(move(uv.y, timeval - 1.0f, 0.3f), 0.0f, chack), 1.0f, floor(uv.x - (1.0f - 0.05f)) * -1.0f);

	return output;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	float2 uv = input.tex;

	float timeVal = fmod(time.x, 2.0f);

	output = Process(uv, timeVal, output);

	return output;
}