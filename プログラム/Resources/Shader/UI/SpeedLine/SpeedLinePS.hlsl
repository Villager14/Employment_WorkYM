#include "SpeedLine.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float Front(float colorPower)
{
	return ceil(clamp(colorPower - time.y, 0.0f, 1.0f));
}

float Back(float colorPower)
{
	return floor(clamp(colorPower - time.x, -1.0f, 0.0f)) * -1.0f;
}

float HerfFront(float colorPower)
{
	return floor(clamp(colorPower - time.y, -1.0f, 0.0f))
			* -1.0f * ceil(colorPower);
}

float HerfBack(float colorPower)
{
	return ceil(clamp(colorPower - time.x, 0.0f, 1.0f));
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	float4 output2 = tex2.Sample(samLinear, float2(input.tex.x, input.tex.y + backTime));

	output2.a = lerp(0.0f, alphaPower, ceil(output2.a));
	
	output = lerp(float4(0.0f, 0.0f, 0.0f, 0.0f),
		output2,
		lerp(Front(output.r) * Back(output.r),
			max(HerfFront(output.r), HerfBack(output.r)), time.z));

	/*
	 output = lerp(float4(0.0f, 0.0f, 0.0f, 0.0f),
				  float4(0.6f, 1.0f, 0.0f, 0.15f),
		lerp(Front(output.r) * Back(output.r),
			max(HerfFront(output.r), HerfBack(output.r)), time.z));
	*/
	return output;
}