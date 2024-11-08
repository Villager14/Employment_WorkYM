#include "FogDepth.hlsli"

Texture2D<float> tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

//		深度描画（近いオブジェクト程黒く遠いオブジェクト程白くなる）
float DepthView(float2 uv)
{
	float output = tex.Sample(samLinear, uv).r;

	float zCamera = drawingDistance.y * drawingDistance.x / 
		(drawingDistance.y - output * (drawingDistance.y - drawingDistance.x));	

	float color = saturate(zCamera / drawingDistance.y);

	return color;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	//		テクスチャ
	float4 output = tex2.Sample(samLinear, input.tex);

	output = lerp(output, backColor, clamp(DepthView(input.tex) - 0.5f, 0.0f, 1.0f) * 2.0f);

	return output;
}