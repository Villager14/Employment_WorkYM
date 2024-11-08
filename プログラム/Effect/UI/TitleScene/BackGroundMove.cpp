/*
* @file		BackGroundMove.h
* @brief	�w�i�̈ړ�
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "BackGroundMove.h"

BackGroundMove::BackGroundMove()
	:
	m_time(0.0f)
{
}

BackGroundMove::~BackGroundMove()
{
}

void BackGroundMove::Initialize()
{
	//		UI�`��̐���
	m_uiRenderManager = std::make_unique<UIRenderManager>();

	//		�V�F�[�_�[�̐���
	m_uiRenderManager->Create(L"Resources/Texture/TitleScene/TitleBack.png",
		L"Resources/Shader/UI/BackGroundMove/BackGroundMoveVS.cso",
		L"Resources/Shader/UI/BackGroundMove/BackGroundMoveGS.cso",
		L"Resources/Shader/UI/BackGroundMove/BackGroundMovePS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	buffer.rotationMatrix = m_uiRenderManager->GetRotationMatrix();

	m_time = 0.0f;
}

void BackGroundMove::Update()
{
	//		�w�i�̈ړ�����
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * BACK_GROUND_SPEED;
}

void BackGroundMove::Render()
{
	//		�R���X�g�o�b�t�@�̒l��ݒ肷��
	buffer.time = { m_time, 0.0f, 0.0f, 0.0f };

	//		�w�i�̕`��
	m_uiRenderManager->Render(buffer);
}

void BackGroundMove::Finalize()
{
	m_uiRenderManager.reset();
}
