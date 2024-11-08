cbuffer ConstBuffer : register(b0)
{
	float4 windowSize;
	float4x4 rotationMatrix;
	float4 time;
	float4 motionVector;			//		���[�V�����̋���	(����)
	float4 blurStrength;			//		�u���[�̋���
	float4 concentrationLineTime;	//
	float4 grayStrength;				//		�O���C�X�P�[���̋���
}

struct VS_INPUT
{
	float3 pos : POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};