/*
* @file		PostEffectCommonProcess.cpp
* @brief	�|�X�g�G�t�F�N�g���ʏ���
* @author	Morita
* @date		2024/10/07
*/

#include "pch.h"

#include "PostEffectCommonProcess.h"

#include "PostEffectManager.h"

PostEffectCommonProcess::PostEffectCommonProcess(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
}

PostEffectCommonProcess::~PostEffectCommonProcess()
{
}

std::unique_ptr<DX::RenderTexture> PostEffectCommonProcess::CreateRenderTexture(DirectX::SimpleMath::Vector2 size)
{
	//		�����_�[�e�N�X�`���̍쐻
	std::unique_ptr<DX::RenderTexture> renderTexture =
		std::make_unique<DX::RenderTexture>(
			LibrarySingleton::GetInstance()->
			GetDeviceResources()->GetBackBufferFormat());

	//		�f�o�C�X�̐ݒ�
	renderTexture->SetDevice(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice());

	//		�T�C�Y�̐ݒ�
	RECT rect = { 0,0, static_cast<int>(size.x), static_cast<int>(size.y) };

	renderTexture->SetWindow(rect);

	return std::move(renderTexture);
}

void PostEffectCommonProcess::CreateTexture(int index)
{
	m_postEffectManager->GetStandardShader()->CreateUIInformation
	(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f }, PostEffectManager::UIType(index));
}
