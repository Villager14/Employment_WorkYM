#include "CoolTime.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t2);
SamplerState samLinear : register(s0);

float pi = 3.14159265359;

float AnglePoint(float minAngle, float maxAngle)
{
	float angle = rotation.x;

	//		0Å`360ìxÇÃä‘Ç∆Ç∑ÇÈ
	float maxval = min(angle - 1.0f - maxAngle, 0.0f);

	maxval = normalize(maxval);

	maxval = abs(maxval);

	float minval = max(angle + 1 - minAngle, 0.0f);

	normalize(minval);
	
	return  maxval * minval;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.tex);

	float2 uv = input.tex;

	float angle = rotation.x;

	float3 vel = float3(0.0f,0.0f,0.0f);

	float a = output.w;

	//		90ìxéñÇ…åvéZÇ∑ÇÈ
	if (angle <= 90.0f)
	{
		float move = angle / 90.0f;

		vel = lerp(float3(0.5f, 0.0f, 0.0f), float3(1.0f, 0.5f, 0.0f), move);
	}
	else if (angle <= 180.0f)
	{
		float move = (angle - 90.0f) / 90.0f;

		vel = lerp(float3(1.0f, 0.5f, 0.0f), float3(0.5f, 1.0f, 0.0f), move);
	}
	else if (angle <= 270.0f)
	{
		float move = (angle - 180.0f) / 90.0f;

		vel = lerp(float3(0.5f, 1.0f, 0.0f), float3(0.0f, 0.5f, 0.0f), move);
	}
	else if (angle <= 360)
	{
		float move = (angle - 270.0f) / 90.0f;

		vel = lerp(float3(0.0f, 0.5f, 0.0f), float3(0.5f, 0.0f, 0.0f), move);
	}

	float3 vv = cross(vel - float3(0.5f, 0.5f, 0.0f), float3(uv.x, uv.y, 0.0f) - float3(0.5f, 0.5f, 0.0f));

	if (vv.z >= 0.0f)
	{
		output.w = 0;
	}

	if (angle <= 180.0f)
	{
		if (uv.x < 0.5f)
		{
			output.w = 0;
		}
	}
	else
	{
		if (uv.x > 0.5f)
		{
			output.w = a;
		}
	}	

	return output;
}