#include "Expansion.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 uv = input.tex;

	//uv.xy *= 2.0f;

	float4 color = tex.Sample(samLinear, uv);

	/*
	float bler = 10.0f;

	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float weight_total = 0;

	//		重み(ガウシアンブラー)
	float weight = exp(-0.5f * pow(0, 2) * 5.0f);

	color = weight * tex.Sample(samLinear, uv
	        + float2(0.0f, 2.0f / windowSize.x));

	weight_total += weight;

	for (float i = 1; i <= bler; i += 1)
	{
		//		現在のピクセルからの距離を取る
		float distance_normalized = abs(i / (bler * 2.0f));

		//		重み(ガウシアンブラー)
		weight = exp(-0.5f * pow(distance_normalized, 2) * 5.0f);

		color += weight * tex.Sample(samLinear, uv
			+ float2(0.0f, 2.0f * i / windowSize.y))
			+ tex.Sample(samLinear, uv
			+ float2(0.0f, -2.0f * i / windowSize.y));
	
		weight_total += weight * 2.0f;
	}

	color /= weight_total;
	//*/

	return color;
}