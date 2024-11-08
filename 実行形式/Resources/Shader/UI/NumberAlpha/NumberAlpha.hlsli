cbuffer ConstBuffer : register(b0)
{
	float4 windowSize;
	float4x4 rotationMatrix;
	int number;
	float3 pad;
	float alpha;
	float3 pad2;
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