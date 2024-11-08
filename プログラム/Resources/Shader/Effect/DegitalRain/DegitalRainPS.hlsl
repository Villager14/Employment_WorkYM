#include "DegitalRain.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

int mod(int a, int b)
{
	return a - (b * (a / b));
}

float Raund(float val)
{
	return floor(val);
}

inline float4 SelectTexture(float2 uv, float val)
{
	return lerp(tex2.Sample(samLinear, uv), tex.Sample(samLinear, uv), Raund(val));
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 uv = input.Tex;

	//�g���̉摜�\��
	float4 output = float4(1.0f, 0.0f, 0.0f, 1.0f);

	//		���̈�
	output = lerp(SelectTexture(uv, (number / 10000) % 10), output, clamp(ceil(uv.y - 3.0f), 0.0f, 1.0f));

	//		��̈�
	output = lerp(SelectTexture(uv, ((number / 1000) % 10)),	output, clamp(ceil(uv.y - 2.0f), 0.0f, 1.0f));

	//		�S�̈�
	output = lerp(SelectTexture(uv, ((number / 100) % 10)),		output, clamp(ceil(uv.y - 1.0f), 0.0f, 1.0f));

	//		�\�̈�
	output = lerp(SelectTexture(uv, ((number / 10) % 10)),		output, clamp(ceil(uv.y), 0.0f, 1.0f));

	//		��̈�
	output = lerp(SelectTexture(uv, (number % 10)), output, clamp(ceil(uv.y + 1.0f), 0.0f, 1.0f));

	return output;
}