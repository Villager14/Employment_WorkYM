/*
* @file		FadeIn.h
* @brief	�t�F�[�h�̏���
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "FadeIn.h"

FadeIn::FadeIn()
	:
	m_time(0.0f),
	m_fadeinResetJudgement(true),
	m_fadeoutResetJudgement(false),
	m_stayTime(0.0f),
	m_firstJudgement(true)
{
	//		�t�F�[�h�`��̐���
	m_fadeRender = std::make_unique<UIRenderManager>();

}

FadeIn::~FadeIn()
{
}

void FadeIn::Initialize()
{
	m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		L"Resources/Shader/UI/Fade/FadeShaderVS.cso",
		L"Resources/Shader/UI/Fade/FadeShaderGS.cso",
		L"Resources/Shader/UI/Fade/FadeShaderPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	buffer.rotationMatrix = m_fadeRender->GetRotationMatrix();

	m_time = 0.0f;

	m_stayTime = 0.0f;
}

void FadeIn::Update(GameManager* gameManager)
{
	//		�I���̏ꍇ
	if (gameManager->FlagJudgement(GameManager::EndJudgement))
	{
		m_stayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		if (m_stayTime <= 1.0f) return;

		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 1.0f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		//		�v���C�V�[���I�����̉��ʒ���
		MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

		if (m_time <= 0.0f)
		{
			//		���̃V�[���ɐ؂�ւ���
			gameManager->TrueFlag(GameManager::NextScene);
		}

		return;
	}

	//		������ԁ��t�F�[�h�A�E�g�����Ȃ���Ԃ̏ꍇ
	if (gameManager->FlagJudgement(GameManager::RevivalJudgement)
		&& !m_fadeoutResetJudgement)
	{
		m_fadeoutResetJudgement = true;

		m_time = 1.0f;
	}

	//		�t�F�[�h�C���̏���
	if (m_fadeinResetJudgement)
	{
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_firstJudgement)
		{
			//		�v���C�V�[���J�n���̉��ʒ���
			MusicLibrary::GetInstance()->SceneLerpVolume(m_time);
		}

		if (m_time > 1.0f)
		{
			m_fadeinResetJudgement = false;
		}
	}

	//		�t�F�[�h�A�E�g�̏���
	if (m_fadeoutResetJudgement)
	{
		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 4.0f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_time <= 0.0f)
		{
			m_fadeoutResetJudgement = false;

			//		������Ԃ��I��
			gameManager->FalseFlag(GameManager::RevivalJudgement);
			gameManager->FalseFlag(GameManager::DeathJudgement);
			m_fadeinResetJudgement = true;
		}
	}
}

void FadeIn::Render()
{
	buffer.time = { Library::Clamp(m_time, 0.0f, 1.0f) , 0.0f, 0.0f, 0.0f };

	m_fadeRender->Render(buffer);
}

void FadeIn::Finalize()
{
	m_fadeRender->Finalize();
}
