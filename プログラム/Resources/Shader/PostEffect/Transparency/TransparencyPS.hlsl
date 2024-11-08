#include "Transparency.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
Texture2D tex3 : register(t2);

SamplerState samLinear : register(s0);

float4 viewColor()
{
	float r = 43.0f;
	float g = 156.0f;
	float b = 8.0f;

	return float4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output3 = tex3.Sample(samLinear, input.tex);

	//		テクスチャ
	float4 output = tex.Sample(samLinear, input.tex);

	//		真っ黒なオブジェクトを描画しない
	output = lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), output, ceil(clamp(output.r + output.g + output.b, 0.0f, 1.0f)));

	
	if (output3.r < 0.3f)
	{
		output.rgb = lerp(tex2.Sample(samLinear, input.tex).rgb, output.rgb, clamp((output3.r * 3.0f) - 0.3f, 0.0f, 1.0f));
	}

	//		アルファが一以上の場合エフェクトを描画
	output = lerp(tex2.Sample(samLinear, input.tex), output, ceil(output.a));

	//float4 backColor = tex2.Sample(samLinear, input.tex);

	//float4 output = tex.Sample(samLinear, input.tex);

	//output.rgb = (output.rgb * output.a) + (backColor * (1 - output.a));

	return output;
}