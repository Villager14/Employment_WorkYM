#include "WarpBler.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 PulasuUV(float2 uv, int index)
{
	float2 uvPostition = uv + float2(0.0f, 2.0f * index / windowSize.y);

	return tex.Sample(samLinear, uvPostition) * (floor(uvPostition.y) * -1.0f + 1.0f);
}

float4 MinasuUV(float2 uv, int index)
{
	float2 uvPostition = uv + float2(0.0f, -2.0f * index / windowSize.y);

	return tex.Sample(samLinear, uvPostition) * ceil(uvPostition.y);
}

float WeightVal(float val)
{
	return exp(-0.5f * pow(val, 2) * blerValue.x);
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 uv = input.tex;

	uv.xy *= 2.0f;

	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float weight_total = 0;

	//		�d��(�K�E�V�A���u���[)
	float weight = WeightVal(0.0f);

	color = weight * tex.Sample(samLinear, uv
	        + float2(0.0f, 2.0f / windowSize.x));

	weight_total += weight;

	int bler = 5;

	for (int i = 1; i <= bler; ++i)
	{
		//		���݂̃s�N�Z������̋��������
		float distance_normalized = abs((float)i / ((float)bler * 5.0f));

		//		�d��(�K�E�V�A���u���[)
		weight = WeightVal(distance_normalized);

		//		�񐔕��|����
		float count = 2.0f;

		//		�摜�ȏ�̕������u���[����ꍇ0�ɂ���
		float4 pUV = PulasuUV(uv, i);

		//		�摜�ȉ��̕������u���[����ꍇ�O�ɂ���
		float4 dUV = MinasuUV(uv, i);

		//		�摜�������ȏꍇ�d�݂����炷
		count -= lerp(1.0f, 0.0f, clamp(ceil(pUV.a), 0.0f, 1.0f));
		count -= lerp(1.0f, 0.0f, clamp(ceil(dUV.a), 0.0f, 1.0f));

		//		�摜�̐F�Əd�݂��|����
		color += weight * (pUV + dUV);

		//		�����I�ȏd�݂ɒǉ�����
		weight_total += weight * count;
	}

	color /= weight_total;

	return color;
}