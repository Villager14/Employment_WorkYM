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
*   �F�̋���
* 
*   @param  (viewcolorPower)    �`�悷��F�̋���
*   @param  (colorPower)        �s�N�Z���̐F�̋���
*   @return 0.0f : �`�悵�Ȃ� 1.0f : �`�悷��
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
*   �`�悷�邩�ǂ���
* 
*   @param  (time)  �`��J�n���鎞��
*   @return 0.0f : �`�悵�Ȃ� 1.0f : �`�悷��
*/
float ViewJudgementTime(float time)
{
    return ceil(clamp(time - Time.x, 0.0f, 1.0f)) * -1.0f + 1.0f;
}

/*
*   �`�悷�邩�ǂ���
* 
*   @param  (viewcolorPower)    �`�悷��F�̋���
*   @param  (changeColor)       �ω���̐F
*   @param  (colorPower)        �F�̋���
*   @param  (color)             ���݂̐F
*   @param  (time)              �`��J�n���鎞��
*   @return �`�悷��F
*/
float3 ViewRange(float viewcolorPower, float3 changeColor, float colorPower, float3 color, float time)
{
   return lerp(color, changeColor, ColorPower(viewcolorPower, colorPower) * ViewJudgementTime(time));
}

float4 main(PS_INPUT input) : SV_Target0
{
    //      �e�N�X�`���̏��
    float4 color = tex.Sample(samLinear, input.TexCoord);

    float4 fantom = tex2.Sample(samLinear, input.TexCoord);

    float4 spray = tex3.Sample(samLinear, input.TexCoord);

    //      ��ڂ̖��
    color.rgb = ViewRange(0.3f, spray.rbg,
            fantom.r, color.rgb, 1.0f);

    //      ��ڂ̖��
    color.rgb = ViewRange(0.6f, spray.rbg,
            fantom.r, color.rgb, 2.0f);

    //      �O�ڂ̖��
    color.rgb = ViewRange(0.9f, spray.rbg,
            fantom.r, color.rgb, 3.0f);

    return color;
}