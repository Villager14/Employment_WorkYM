#include "FrameWalk.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);


float move(float uv, float timeval, float length)
{
	float a = floor(lerp(0.0f - length, 1.0f, timeval) - uv) * -1.0f;
	float b = ceil(lerp(0.0f, 1.0f + length, timeval) - uv);

	return b * a;
}

static const float MOVE_LENGTH = 0.1f;

float2 UP(float2 uv)
{
	uv.y -= 1.0f;
	uv.y += clamp(time.x, 0.0f, 1.0f);

	//float4 output = tex.Sample(samLinear, uv);

	return uv;
}

float4 Under(float2 uv)
{
	uv.y -= time.y * MOVE_LENGTH;

	uv.x += time.y * MOVE_LENGTH * (windowSize.y / windowSize.x) * lerp(1, -1, ceil(uv.x - 0.5f));

	uv = UP(uv);

	float4 output = tex.Sample(samLinear, uv);

	//		0.5à»â∫ÇÃílÇè¡Ç∑
	output.w *= ceil(uv.y - 0.5f);
	output.w *= ceil(uv.y);

	return output;
}

float4 Above(float2 uv)
{
	uv.y += time.y * MOVE_LENGTH;

	uv.x += time.y * MOVE_LENGTH * (windowSize.y / windowSize.x) * lerp(1, -1, ceil(uv.x - 0.5f));

	uv = UP(uv);

	float4 output = tex.Sample(samLinear, uv);

	//		0.5à»â∫ÇÃílÇè¡Ç∑
	output.w *= floor(uv.y - 0.5f) * -1.0f;
	output.w *= ceil(uv.y);

	return output;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 uv = input.tex;

	float4 output = lerp(Above(uv), Under(uv), ceil(uv.y - 0.5f));

	return output;
}