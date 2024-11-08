/*
* @file		UIRender.cpp
* @brief	UI�̕`�揈��
* @author	Morita
* @date		2024/10/20
*/

#include "pch.h"

#include "UIRender.h"

#include "Common/ReaData.h"

UIRender::UIRender(PostEffectManager* manager)
	:
	m_postEffectManager(manager)
{
}

UIRender::~UIRender()
{
}

void UIRender::Initialize()
{
	CreateRenderTarget();
}

void UIRender::Update()
{
}

void UIRender::ObjectRender()
{
	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|���Ȃ��悤�ɂ���
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		�w�i�F�����ɂ���
	m_postEffectManager->SetBackRenderColor(DirectX::Colors::Black);

	//		�����_�[�^�[�Q�b�g�̕ύX(�I�u�W�F�N�g�̕`��)
	m_alphaEffectTexture = m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());

	//		�e�N�X�`�����Z�b�g����
	m_postEffectManager->GetStandardShader()->ChangeTexture(PostEffectManager::UIType::UITexture,
		m_postEffectManager->GetShaderTexture(),
		LibrarySingleton::GetInstance()->GetScreenSize());

	//		�e�N�X�`����`�悷��
	m_postEffectManager->GetStandardShader()->Render(PostEffectManager::UIType::UITexture);
}

void UIRender::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_alphaEffectTexture);
}

void UIRender::Filanize()
{
	m_renderTexture.reset();
}

void UIRender::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
