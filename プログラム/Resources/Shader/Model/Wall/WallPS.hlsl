#include "Wall.hlsli"

struct PS_INPUT
{
    float2 TexCoord   : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS   : TEXCOORD2;
    float4 LightPosPS   : TEXCOORD3;
    float4 PositionPS   : SV_Position;
};

/*
*   色の強さ
* 
*   @param  (viewcolorPower)    描画する色の強さ
*   @param  (colorPower)        ピクセルの色の強さ
*   @return 0.0f : 描画しない 1.0f : 描画する
*/
float ColorPower(float viewcolorPower, float power)
{
    if (power < viewcolorPower)
    {
        return 1.0f;
    }

    return 0.0f;
}

/*
*   描画するかどうか
* 
*   @param  (time)  描画開始する時間
*   @return 0.0f : 描画しない 1.0f : 描画する
*/
float ViewJudgementTime(float time)
{
    return ceil(clamp(time - Time.x, 0.0f, 1.0f)) * -1.0f + 1.0f;
}

/*
*   描画するかどうか
* 
*   @param  (viewcolorPower)    描画する色の強さ
*   @param  (changeColor)       変化後の色
*   @param  (colorPower)        色の強さ
*   @param  (color)             現在の色
*   @param  (time)              描画開始する時間
*   @return 描画する色
*/
float3 ViewRange(float viewcolorPower, float3 changeColor, float colorPower, float3 color, float time)
{
   return lerp(color, changeColor, ColorPower(viewcolorPower, colorPower) * ViewJudgementTime(time));
}

float4 main(PS_INPUT input) : SV_Target0
{
    //      テクスチャの情報
    float4 color = tex.Sample(samLinear, input.TexCoord);

    float4 fantom = tex2.Sample(samLinear, input.TexCoord);

    float4 spray = tex3.Sample(samLinear, input.TexCoord);

    //      一つ目の矢印
    color.rgb = ViewRange(0.3f, spray.rbg,
            fantom.r, color.rgb, 1.0f);

    //      二つ目の矢印
    color.rgb = ViewRange(0.6f, spray.rbg,
            fantom.r, color.rgb, 2.0f);

    //      三つ目の矢印
    color.rgb = ViewRange(0.9f, spray.rbg,
            fantom.r, color.rgb, 3.0f);

    return color;
}