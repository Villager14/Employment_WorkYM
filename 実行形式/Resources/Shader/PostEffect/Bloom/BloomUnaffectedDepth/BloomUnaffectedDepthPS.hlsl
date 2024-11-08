#include "BloomUnaffectedDepth.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

//		深度描画（近いオブジェクト程黒く遠いオブジェクト程白くなる）
float DepthView(float2 uv)
{
	float output = tex.Sample(samLinear, uv).r;

	float2 drawingDistance = float2(0.1f, 370.0f);

	float zCamera = drawingDistance.y * drawingDistance.x /
		(drawingDistance.y - output * (drawingDistance.y - drawingDistance.x));

	float color = saturate(zCamera / drawingDistance.y);

	return color;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float output = lerp(1.0f, 0.0f, DepthView(input.tex));

	return float4(output, output, output, 1.0f);
}