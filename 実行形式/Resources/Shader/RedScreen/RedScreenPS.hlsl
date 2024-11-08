#include "RedScreen.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
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

float4 blur(float2 uv)
{
	float power = 0.1f;
	float center = 1.0f - power * 9.0f;

	float4 output = 0;

	for (int i = 0; i < 9; i++)
	{
		output += tex.Sample(samLinear, uv
			+ float2(((i % 3.0f) - 1.0f) * 0.01f,
			((i / 3.0f) - 1.0f) * 0.01f)) * power;
	}

	output += tex.Sample(samLinear, uv) * center;

	///*		消すとぼかし状態になる
	output = tex.Sample(samLinear, uv);
	//*/

	return output;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	//		色情報を受け取る
	float4 output = tex.Sample(samLinear, input.tex);

	float4 sepiaVal = Sepia(output);

	float elapsedTime = lerp(0.0f, 0.5f, clamp(time.x, 0.0f, 1.0f));

	output = blur(input.tex);

	//		時間経過により色を変える
	output.r = lerp(output.r, sepiaVal.x, elapsedTime);
	output.g = lerp(output.g, sepiaVal.y, elapsedTime);
	output.b = lerp(output.b, sepiaVal.z, elapsedTime);


	//		グレイスケール
	float gray = Gray(output);

	output.r = lerp(output.r, gray, grayStrength.x);
	output.g = lerp(output.g, gray, grayStrength.x);
	output.b = lerp(output.b, gray, grayStrength.x);

	
	float alpha = 1.0f;

	return output;
}