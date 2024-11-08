Texture2D<float4> tex : register(t0);
Texture2D<float4> tex2 : register(t1);
Texture2D<float4> tex3 : register(t2);
Texture2D<float4> normalMap : register(t3);

SamplerState samLinear : register(s0);

cbuffer Parameters : register(b0)
{
    float4 DiffuseColor             : packoffset(c0);	// �f�B�t���[�Y�F
    float3 EmissiveColor            : packoffset(c1);	// �G�~�b�V�u�F
    float3 SpecularColor            : packoffset(c2);	// �X�y�L�����F
    float  SpecularPower : packoffset(c2.w);	// �X�y�L�����̋��x

    float3 LightDirection[3]        : packoffset(c3);	// ���C�g�̕���
    float3 LightDiffuseColor[3]     : packoffset(c6);	// ���C�g�̐F
    float3 LightSpecularColor[3]    : packoffset(c9);	// ���C�g�̃X�y�L�����F

    float3 EyePosition              : packoffset(c12);	// �J�����̈ʒu

    float3 FogColor                 : packoffset(c13);	// �t�H�O�̐F
    float4 FogVector                : packoffset(c14);	// �t�H�O�̂�����

    float4x4 World                  : packoffset(c15);	// ���[���h�s��
    float3x3 WorldInverseTranspose  : packoffset(c19);	// ���[���h�t�]�u�s��
    float4x4 WorldViewProj          : packoffset(c22);	// ���[���h�s�� �~ �r���[�s�� �~ �v���W�F�N�V�����s��
};

//      �R���X�g�o�b�t�@
cbuffer ConstBuffer : register(b1)
{
    float4 Time;            //      ����
}