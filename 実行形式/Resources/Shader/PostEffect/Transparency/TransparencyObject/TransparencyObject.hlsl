cbuffer ConstBuffer : register(b0)
{
    float4 fogColor;        //      フォグの色
    float4 fogLength;       //      フォグの変化距離
    float4 cameraPosition;  //      カメラの座標
    float4 fogJudgement;    //      フォグ処理を行うかどうか？
};

Texture2D<float4> tex : register(t0);
sampler Sampler : register(s0);

struct PS_INPUT
{
    float2 TexCoord   : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS   : TEXCOORD2;
    float4 Diffuse    : COLOR0;
};

float4 main(PS_INPUT pin) : SV_Target0
{
    return float4(0.0f, 0.0f, 0.0f, 1.0f);
}