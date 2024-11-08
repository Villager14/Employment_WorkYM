/*
* @file		ClockTime.h
* @brief	UI���v�̐���
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "ClockTime.h"

ClockTime::ClockTime(GameManager* gameManager)
	:
	m_time(0),
	m_limitTime(0.0f),
	m_gameManager(gameManager)
{
}

ClockTime::~ClockTime()
{
}

void ClockTime::Initialize()
{
	//		�V�F�[�_�[�`��}�l�[�W���[�̐���
	m_shader = std::make_unique<UIRenderManager>();

	//		�����V�F�[�_�[�̍쐻
	m_shader->Create(L"Resources/Texture/UI/Clock/ClockNumber.png",
		L"Resources/Shader/UI/Number/NumberVS.cso",
		L"Resources/Shader/UI/Number/NumberGS.cso",
		L"Resources/Shader/UI/Number/NumberPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 0.8f, 0.8f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	buffer.rotationMatrix = m_shader->GetRotationMatrix();

	m_time = 0;

	m_limitTime = m_gameManager->GetLimitTime();
}

void ClockTime::Update(float elapsedTime)
{
	m_time = static_cast<int>(m_limitTime - elapsedTime);

	if (m_time <= 0.0f)
	{
		//		���Ԑ؂�
		m_gameManager->TrueFlag(GameManager::Flag::TimeLimitJudgement);
	}
}

void ClockTime::Render()
{
	//		�\���P��
	m_shader->SetPosition(TEN_PLACE_MINUTES_POSITION);
	buffer.number = { static_cast<float>(m_time / 60 / 10), 0.0f, 0.0f, 0.0f };

	//		�`��
	m_shader->Render(buffer);

	//		���P��
	m_shader->SetPosition(ONE_PLACE_MINUTES_POSITION);
	buffer.number = { static_cast<float>(m_time / 60 % 10), 0.0f, 0.0f, 0.0f };

	//		�`��
	m_shader->Render(buffer);

	//		�\�b
	m_shader->SetPosition(TEN_PLACE_SECONDS_POSITION);
	buffer.number = { static_cast<float>(m_time % 60 / 10), 0.0f, 0.0f, 0.0f };

	//		�`��
	m_shader->Render(buffer);

	//		�b
	m_shader->SetPosition(ONE_PLACE_SECONDS_POSITION);
	buffer.number = { static_cast<float>(m_time % 60 % 10), 0.0f, 0.0f, 0.0f };

	//		�`��
	m_shader->Render(buffer);
}

void ClockTime::Finalize()
{
	m_shader.reset();
}
