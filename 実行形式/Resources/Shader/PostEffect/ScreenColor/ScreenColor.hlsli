cbuffer ConstBuffer : register(b0)
{
	float4 windowSize;
	float4x4 rotationMatrix;
	float elapsedTime;
	float4 screenColor;
}

struct VS_INPUT
{
	float3 pos : POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 pos   : SV_POSITION;
	float4 color : COLOR;
	float2 tex   : TEXCOORD;
};