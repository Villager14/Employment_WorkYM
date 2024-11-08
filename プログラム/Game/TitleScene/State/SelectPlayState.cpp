/*
* @file		SelectPlayerState.cpp
* @brief	�v���C��I���������
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "SelectPlayState.h"

SelectPlayState::SelectPlayState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f)
{
}

SelectPlayState::~SelectPlayState()
{
}

void SelectPlayState::Initialize()
{
	m_titleSelectManager->GetAnimation()->ChangeState(AnimationManager::Stay);
}

void SelectPlayState::Update()
{
	//		�L�[���͏���
	m_titleSelectManager->InputKey();

	//		UI�̈ړ�����
	UIMove();

	//		�V�[���؂�ւ�����
	ChangeSceneProcess();
}

void SelectPlayState::Render()
{
}

void SelectPlayState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);
	m_time = 0.0f;
}

void SelectPlayState::UIMove()
{
	//		�L�[�������Ȃ������ꍇ���������Ȃ�
	if (!m_titleSelectManager->GetInformation()->GetKeyInput()) return;

	//		�o�ߎ�k��
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetInformation()->MOVE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		�L�[
	float key = sqrt(1.0f - pow(m_time - 1.0f, 2.0f));

	//		��Ɉړ�
	if (m_titleSelectManager->GetInformation()->GetDirection())
	{
		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::UP,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Play);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Down,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Setting);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Back,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::End);
	
		//		Space���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::Space].position =
		DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_PLAY,
			m_titleSelectManager->GetInformation()->SPACE_SETTING, key);

		/*
		//		W���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position = 
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_END,
				m_titleSelectManager->GetInformation()->W_PLAY, key);

		//		A���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_SETTING,
				m_titleSelectManager->GetInformation()->A_END, key);
		*/
	}
	//		���Ɉړ�
	else
	{
		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::UP,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::End);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Down,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Play);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Back,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Setting);
	
		//		Space���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::Space].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_PLAY,
				m_titleSelectManager->GetInformation()->SPACE_END, key);
	
		/*
		//		W���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_END,
				m_titleSelectManager->GetInformation()->W_SETTING, key);

		//		A���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_SETTING,
				m_titleSelectManager->GetInformation()->A_PLAY, key);
		*/
	}
}

void SelectPlayState::ChangeSceneProcess()
{
	//		���Ԃ��P�ȉ��̏ꍇ���������Ȃ�
	if (m_time < 1.0f)
	{
		//		�L�[�{�[�h�̎擾
		DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

		//		�{�^���̎擾
		DirectX::Mouse::ButtonStateTracker button = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

		if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
			button.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			//		�I���I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleInformation::State::ChangState);
		}
	}
	else
	{

		//		�ړ������ɂ���ď�Ԃ�؂�ւ���
		if (!m_titleSelectManager->GetInformation()->GetDirection())
		{
			//		�I���I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleInformation::State::EndState);
		}
		else
		{
			//		�ݒ�I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleInformation::State::SettingState);
		}
	}
}
