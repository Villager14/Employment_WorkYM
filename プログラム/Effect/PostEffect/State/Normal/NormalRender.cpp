/*
* @file		UIRender.cpp
* @brief	UI�̕`�揈��
* @author	Morita
* @date		2024/10/20
*/

#include "pch.h"

#include "NormalRender.h"
#include "Common/ReaData.h"

NormalRender::NormalRender(PostEffectManager* manager)
	:
	m_postEffectManager(manager)
{
}

NormalRender::~NormalRender()
{
}

void NormalRender::Initialize()
{
	CreateRenderTarget();
}

void NormalRender::Update()
{
}

void NormalRender::ObjectRender()
{
	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|���Ȃ��悤�ɂ���
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		�w�i�F�����ɂ���
	m_postEffectManager->SetBackRenderColor(DirectX::Colors::Black);

	//		�����_�[�^�[�Q�b�g�̕ύX(�I�u�W�F�N�g�̕`��)
	m_alphaEffectTexture = m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());
}

void NormalRender::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_alphaEffectTexture);
}

void NormalRender::Filanize()
{
	m_renderTexture.reset();
}

void NormalRender::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
