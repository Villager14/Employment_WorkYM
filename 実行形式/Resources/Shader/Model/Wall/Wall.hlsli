Texture2D<float4> tex : register(t0);
Texture2D<float4> tex2 : register(t1);
Texture2D<float4> tex3 : register(t2);
Texture2D<float4> normalMap : register(t3);

SamplerState samLinear : register(s0);

cbuffer Parameters : register(b0)
{
    float4 DiffuseColor             : packoffset(c0);	// ディフューズ色
    float3 EmissiveColor            : packoffset(c1);	// エミッシブ色
    float3 SpecularColor            : packoffset(c2);	// スペキュラ色
    float  SpecularPower : packoffset(c2.w);	// スペキュラの強度

    float3 LightDirection[3]        : packoffset(c3);	// ライトの方向
    float3 LightDiffuseColor[3]     : packoffset(c6);	// ライトの色
    float3 LightSpecularColor[3]    : packoffset(c9);	// ライトのスペキュラ色

    float3 EyePosition              : packoffset(c12);	// カメラの位置

    float3 FogColor                 : packoffset(c13);	// フォグの色
    float4 FogVector                : packoffset(c14);	// フォグのかかり具合

    float4x4 World                  : packoffset(c15);	// ワールド行列
    float3x3 WorldInverseTranspose  : packoffset(c19);	// ワールド逆転置行列
    float4x4 WorldViewProj          : packoffset(c22);	// ワールド行列 × ビュー行列 × プロジェクション行列
};

//      コンストバッファ
cbuffer ConstBuffer : register(b1)
{
    float4 Time;            //      時間
}