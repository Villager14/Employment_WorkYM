#include "Synthetic.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
Texture2D tex3 : register(t2);
Texture2D<float> tex4 : register(t3);
SamplerState samLinear : register(s0);

//		深度描画（近いオブジェクト程黒く遠いオブジェクト程白くなる）
float DepthView(float2 uv)
{
	float output = tex4.Sample(samLinear, uv).r;

	float2 drawingDistance = float2(0.1f, 370.0f);

	float zCamera = drawingDistance.y * drawingDistance.x /
		(drawingDistance.y - output * (drawingDistance.y - drawingDistance.x));

	float color = saturate(zCamera / drawingDistance.y);

	return color;
}

float4 Light(float2 uv)
{
	float4 output = tex.Sample(samLinear, uv);
	float4 output2 = tex2.Sample(samLinear, uv);

	output2.rgb += output.rgb;

	return output2;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output2 = tex2.Sample(samLinear, input.tex);
	float4 output3 = tex3.Sample(samLinear, input.tex);

	float viewObjectVal = lerp(1.0f, 0.0f, DepthView(input.tex));

	return lerp(output2, Light(input.tex), ceil(viewObjectVal - output3.r));
}