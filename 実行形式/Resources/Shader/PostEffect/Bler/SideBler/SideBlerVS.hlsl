#include "SideBler.hlsli"

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.pos = float4(input.pos, 1);

	//		基本テクセルのUV座標
	float2 tex = input.tex;

	output.color = input.color;
	output.tex = input.tex;

	//output.tex.x += 0.5f;

	return output;
}