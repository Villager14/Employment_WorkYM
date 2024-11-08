#include "SpeedScreen.hlsli"

static const unsigned int vnum = 4;

static const float4 offset_array[vnum] =
{
	float4(0.0f, 1.0f, 0.0f, 1.0f),		//		左上
	float4(1.0f, 1.0f, 0.0f, 1.0f),		//		右上
	float4(0.0f, 0.0f, 0.0f, 1.0f),		//		左下
	float4(1.0f, 0.0f, 0.0f, 1.0f),		//		右下
};

[maxvertexcount(vnum)]
void main(point PS_INPUT input[1],
	inout TriangleStream<PS_INPUT> output)
{
	
	for (uint i = 0; i < vnum; i++)
	{
		//		ジオメトリ出力
		PS_INPUT element;

		//		頂点に入れていた諸々を受け取る
		float2 window = windowSize.xy;
		float4 rect = input[0].color;
		float2 pos = (rect.xy / window.xy) * 2.0f;
		float2 size = (rect.zw / window.xy);

		float2 scale = input[0].pos.xy;

		//		アンカータイプごとに補正する座標を決定する
		uint anc = input[0].pos.z;
		float2 anchor;
		anchor.x = (size.x) * (anc % 3u) * scale.x;
		anchor.y = (size.y) * (anc / 3u) * scale.y;

		//		頂点座標等から配置を決める
		element.pos.xy = pos + scale * size * offset_array[i].xy * 2.0f - float2(1.0f, 1.0f);


		element.pos.xy -= anchor;
		element.pos.x *= window.x / window.y;
		element.pos.y *= -1;


		//		XY平面なのでZは０Wは１
		element.pos.z = 0.0f;
		element.pos.w = 1.0f;
		
		//		回転
		matrix rot = rotationMatrix;
		rot._11 *= window.y / window.x;
		rot._21 *= window.y / window.x;

		element.pos = mul(element.pos, rot);

		//element.pos.x /= 10.0f;

		//		色情報
		element.color = float4(input[0].tex.x, 1.0f, 1.0f, 1.0f);

		//		テクスチャのUV座標
		element.tex = offset_array[i].xy;

		output.Append(element);

	}
	

	output.RestartStrip();
}