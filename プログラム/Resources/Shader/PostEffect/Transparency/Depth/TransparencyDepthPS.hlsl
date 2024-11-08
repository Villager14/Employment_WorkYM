#include "TransparencyDepth.hlsli"

Texture2D<float> tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

//		�[�x�`��i�߂��I�u�W�F�N�g�����������I�u�W�F�N�g�������Ȃ�j
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
	//		�e�N�X�`��
	float4 output = tex2.Sample(samLinear, input.tex);

	float depth = DepthView(input.tex);

	return depth;
}