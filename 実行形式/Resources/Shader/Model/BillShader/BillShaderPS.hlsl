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
    float4 color = tex.Sample(Sampler, pin.TexCoord);

    return color;
}