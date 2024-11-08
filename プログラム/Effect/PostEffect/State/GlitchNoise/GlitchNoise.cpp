/*
* @file		GlitchNoise.h
* @brief	�O���b�`�m�C�Y
* @author	Morita
* @date		2024/10/22
*/

#include "pch.h"

#include "GlitchNoise.h"

#include "Common/ReaData.h"

GlitchNoise::GlitchNoise(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
}

GlitchNoise::~GlitchNoise()
{
}

void GlitchNoise::Initialize()
{
	CreateRenderTarget();

	//		�[�x�V�F�[�_�[�`��
	m_depthShaderView = std::make_unique<UIRenderManager>();

	//		�����p
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/GlitchNoise/GlitchNoiseVS.cso",
		L"Resources/Shader/PostEffect/GlitchNoise/GlitchNoiseGS.cso",
		L"Resources/Shader/PostEffect/GlitchNoise/GlitchNoisePS.cso",
		m_constBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�萔�o�b�t�@�̒l
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
}

void GlitchNoise::Update()
{

}

void GlitchNoise::ObjectRender()
{
	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|���Ȃ��悤�ɂ���
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		�����_�[�^�[�Q�b�g�̕ύX(�I�u�W�F�N�g�̕`��)
	m_colorTexture = m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());

	//		�e�N�X�`���T�C�Y�̕ύX
	m_depthShaderView->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		�e�N�X�`�����Z�b�g����
	m_depthShaderView->SetTexture(m_postEffectManager->GetShaderTexture());

	//		Color�����̕`��
	m_depthShaderView->Render(m_constBuffer);
}

void GlitchNoise::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_colorTexture);
}

void GlitchNoise::Filanize()
{
	m_renderTexture.reset();

	m_depthShaderView.reset();
}

void GlitchNoise::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
