/*
* @file		SelectSettingState.cpp
* @brief	�ݒ��I���������
* @author	Morita
* @date		2024/05/26
*/

#include "pch.h"

#include "SelectSettingState.h"

SelectSettingState::SelectSettingState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f)
{
}

SelectSettingState::~SelectSettingState()
{
}

void SelectSettingState::Initialize()
{
	m_titleSelectManager->GetAnimation()->ChangeState(AnimationManager::Sliding);
}

void SelectSettingState::Update()
{
	//		�L�[���͏���
	m_titleSelectManager->InputKey();
	
	//		UI�̈ړ�����
	UIMove();

	//		�V�[���؂�ւ�����
	ChangeSceneProcess();

}

void SelectSettingState::Render()
{
}

void SelectSettingState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);
	m_time = 0.0f;
}

void SelectSettingState::UIMove()
{
	//		�L�[�������Ȃ������ꍇ���������Ȃ�
	if (!m_titleSelectManager->GetInformation()->GetKeyInput()) return;

	//		�o�ߎ���
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetInformation()->MOVE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		�L�[
	float key = m_time;//1.0f - pow(1.0f - m_time, 4.0f);

	//		��Ɉړ�
	if (m_titleSelectManager->GetInformation()->GetDirection())
	{
		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::UP,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Setting);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Down,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::End);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Back,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Play);
	
		//		Space���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::Space].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_SETTING,
				m_titleSelectManager->GetInformation()->SPACE_END, key);
	
		/*
		//		W���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_PLAY,
				m_titleSelectManager->GetInformation()->W_SETTING, key);

		//		A���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_END,
				m_titleSelectManager->GetInformation()->A_PLAY, key);
				*/
	}
	//		���Ɉړ�
	else
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
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_SETTING,
				m_titleSelectManager->GetInformation()->SPACE_PLAY, key);
	
		/*
		//		W���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_PLAY,
				m_titleSelectManager->GetInformation()->W_END, key);
	
		//		A���W�̑J��
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_END,
				m_titleSelectManager->GetInformation()->A_SETTING, key);
		*/
	}
}

void SelectSettingState::ChangeSceneProcess()
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
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

			//		���j���[���J��
			m_titleSelectManager->GetMenuInformation()->SetMenuJudgement(true);
		}
	}
	else
	{

		if (m_titleSelectManager->GetInformation()->GetDirection())
		{
			//		�ݒ�I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleInformation::State::EndState);
		}
		else
		{
			//		�I���I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleInformation::State::PlayState);
		}
	}
}
