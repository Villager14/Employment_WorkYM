/*
* @file		ScreenColor.h
* @brief	�X�N���[���̐F
* @author	Morita
* @date		2024/10/21
*/

#include "pch.h"

#include "ScreenColor.h"

#include "Common/ReaData.h"

ScreenColor::ScreenColor(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager),
	m_elapsedTime(0.0f),
	m_menuOpenJudgement(false)
{
}

ScreenColor::~ScreenColor()
{
}

void ScreenColor::Initialize()
{
	CreateRenderTarget();

	//		�[�x�V�F�[�_�[�`��
	m_depthShaderView = std::make_unique<UIRenderManager>();

	//		�����p
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/ScreenColor/ScreenColorVS.cso",
		L"Resources/Shader/PostEffect/ScreenColor/ScreenColorGS.cso",
		L"Resources/Shader/PostEffect/ScreenColor/ScreenColorPS.cso",
		m_constBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�萔�o�b�t�@�̒l
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_constBuffer.elasedTime = 0.0f;
	m_constBuffer.color = { 1.0f, 0.0f, 0.0f, 1.0f };

	m_elapsedTime = 0.0f;

}

void ScreenColor::Update()
{
	if (RedScreen()) return;

	if (GrayScreen()) return;

	m_elapsedTime = 0.0f;
}

void ScreenColor::ObjectRender()
{
	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|���Ȃ��悤�ɂ���
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	m_constBuffer.elasedTime = m_elapsedTime;

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

void ScreenColor::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_colorTexture);
}

void ScreenColor::Filanize()
{
	m_renderTexture.reset();

	m_elapsedTime = 0.0f;

	m_menuOpenJudgement = 0.0f;

	m_depthShaderView.reset();
}

bool ScreenColor::RedScreen()
{
	//		���S�����ꍇ
	if (m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::DeathJudgement) ||
		m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::TimeLimitJudgement))
	{
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

		//		�F��Ԃɂ���
		m_constBuffer.color = { 1.0f, 0.0f, 0.0f, 1.0f };

		//		���Ԃ��R���X�g�o�b�t�@�ɑ������
		m_constBuffer.elasedTime = m_elapsedTime;

		return true;
	}

	return false;
}

bool ScreenColor::GrayScreen()
{
	//		���j���[���J������
	if (m_postEffectManager->GetMenuInformation()->GetMenuTransrationJudgement() && !m_menuOpenJudgement)
	{
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

		m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

		//		�F���O���[�ɂ���
		m_constBuffer.color = { 0.5f, 0.5f, 0.5f, 1.0f };

		if (m_elapsedTime >= 1.0f)
		{
			//		���j���[���J���Ă����Ԃɂ���
			m_menuOpenJudgement = true;
		}

		return true;
	}

	//		���j���[���J���Ă��鎞
	if (m_menuOpenJudgement && !m_postEffectManager->GetMenuInformation()->GetMenuTransrationJudgement())
	{
		m_elapsedTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

		m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

		if (m_elapsedTime <= 0.0f)
		{
			//		���j���[���J���Ă����Ԃɂ���
			m_menuOpenJudgement = false;
		}

		return true;
	}

	//		���j���[���J���Ă����Ԃ̏ꍇ�͏��������Ȃ�
	if (m_menuOpenJudgement) return true;

	return false;
}

void ScreenColor::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
