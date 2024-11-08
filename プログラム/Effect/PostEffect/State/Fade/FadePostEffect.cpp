/*
* @file		ScreenColor.h
* @brief	�X�N���[���̐F
* @author	Morita
* @date		2024/10/21
*/

#include "pch.h"

#include "FadePostEffect.h"

#include "Common/ReaData.h"

FadePostEffect::FadePostEffect(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager),
	m_fadeStayTime(0.0f),
	m_fadeinResetJudgement(true),
	m_fadeoutResetJudgement(false),
	m_firstJudgement(true)
{
}

FadePostEffect::~FadePostEffect()
{
}

void FadePostEffect::Initialize()
{
	CreateRenderTarget();

	//		�[�x�V�F�[�_�[�`��
	m_depthShaderView = std::make_unique<UIRenderManager>();

	//		�����p
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/UI/Fade/FadeShaderVS.cso",
		L"Resources/Shader/UI/Fade/FadeShaderGS.cso",
		L"Resources/Shader/UI/Fade/FadeShaderPS.cso",
		m_constBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�萔�o�b�t�@�̒l
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_constBuffer.time = { 0.0f, 0.0f, 0.0f, 0.0f };

	m_fadeStayTime = 0.0f;
}

void FadePostEffect::Update()
{
	Fade();
}

void FadePostEffect::ObjectRender()
{
	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|���Ȃ��悤�ɂ���
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	m_constBuffer.time = { m_fadeTime, 0.0f, 0.0f, 0.0f };

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

void FadePostEffect::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_colorTexture);
}

void FadePostEffect::Filanize()
{
	m_renderTexture.reset();
	m_depthShaderView.reset();
	m_fadeStayTime = 0.0f;
	m_fadeinResetJudgement = true;
	m_fadeoutResetJudgement = false;
	m_firstJudgement = true;
}

void FadePostEffect::Fade()
{
	//		�I���̏ꍇ
	if (m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::EndJudgement))
	{
		m_fadeStayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		if (m_fadeStayTime <= 1.0f) return;

		m_fadeTime -= LibrarySingleton::GetInstance()->GetElpsedTime();

		m_fadeTime = Library::Clamp(m_fadeTime, 0.0f, 1.0f);

		//		�v���C�V�[���I�����̉��ʒ���
		MusicLibrary::GetInstance()->SceneLerpVolume(m_fadeTime);

		if (m_fadeTime <= 0.0f)
		{
			//		���̃V�[���ɐ؂�ւ���
			m_postEffectManager->GetGameManager()->TrueFlag(GameManager::NextScene);
		}

		return;
	}

	//		������ԁ��t�F�[�h�A�E�g�����Ȃ���Ԃ̏ꍇ
	if (m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::RevivalJudgement)
		&& !m_fadeoutResetJudgement)
	{
		m_fadeoutResetJudgement = true;

		m_fadeTime = 1.0f;
	}

	//		�t�F�[�h�C���̏���
	if (m_fadeinResetJudgement)
	{
		m_fadeTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

		m_fadeTime = Library::Clamp(m_fadeTime, 0.0f, 1.0f);

		if (m_firstJudgement)
		{
			//		�v���C�V�[���J�n���̉��ʒ���
			MusicLibrary::GetInstance()->SceneLerpVolume(m_fadeTime);
		}

		if (m_fadeTime >= 1.0f)
		{
			m_fadeinResetJudgement = false;
		}
	}

	//		�t�F�[�h�A�E�g�̏���
	if (m_fadeoutResetJudgement)
	{
		m_fadeTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 4.0f;

		m_fadeTime = Library::Clamp(m_fadeTime, 0.0f, 1.0f);

		if (m_fadeTime <= 0.0f)
		{
			//		�^�C�����~�b�g
			if (m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::TimeLimitJudgement))
			{
				//		���̃V�[���ɐ؂�ւ���
				m_postEffectManager->GetGameManager()->TrueFlag(GameManager::NextScene);

				return;
			}

			m_fadeoutResetJudgement = false;

			//		������Ԃ��I��
			m_postEffectManager->GetGameManager()->FalseFlag(GameManager::RevivalJudgement);
			m_postEffectManager->GetGameManager()->FalseFlag(GameManager::DeathJudgement);
			m_fadeinResetJudgement = true;
		}
	}
}

void FadePostEffect::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
