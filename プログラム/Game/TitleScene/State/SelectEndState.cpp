/*
* @file		SelectEndState.cpp
* @brief	終了を選択した状態
* @author	Morita
* @date		2024/05/26
*/
#include "pch.h"

#include "SelectEndState.h"

SelectEndState::SelectEndState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f)
{
}

SelectEndState::~SelectEndState()
{
}

void SelectEndState::Initialize()
{
	m_titleSelectManager->GetAnimation()->ChangeState(AnimationManager::Upright);
}

void SelectEndState::Update()
{
	//		キー入力処理
	m_titleSelectManager->InputKey();

	//		UIの移動処理
	UIMove();

	//		シーン切り替え処理
	ChangeSceneProcess();
}

void SelectEndState::Render()
{
}

void SelectEndState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);
	m_time = 0.0f;
}

void SelectEndState::UIMove()
{
	//		キー処理がなかった場合処理をしない
	if (!m_titleSelectManager->GetInformation()->GetKeyInput()) return;

	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetInformation()->MOVE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		キー
	float key = Library::Clamp(m_time, 0.0f, 1.0f);

	//		上に移動
	if (m_titleSelectManager->GetInformation()->GetDirection())
	{
		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::UP,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::End);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Down,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Play);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Back,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Setting);
	
		//		Space座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::Space].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_END,
				m_titleSelectManager->GetInformation()->SPACE_PLAY, key);
	
		/*
		//		W座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_SETTING,
				m_titleSelectManager->GetInformation()->W_END, key);

		//		A座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_PLAY,
				m_titleSelectManager->GetInformation()->A_SETTING, key);
		*/
	}
	//		下に移動
	else
	{
		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::UP,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Setting);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Down,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::End);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Back,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Play);
	
		//		Space座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::Space].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_END,
				m_titleSelectManager->GetInformation()->SPACE_SETTING, key);
	
		/*
		//		W座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_SETTING,
				m_titleSelectManager->GetInformation()->W_PLAY, key);
	
		//		A座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_PLAY,
				m_titleSelectManager->GetInformation()->A_END, key);
				*/
	}
}

void SelectEndState::ChangeSceneProcess()
{
	//		時間が１以下の場合処理をしない
	if (m_time < 1.0f)
	{
		//		キーボードの取得
		DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

		//		ボタンの取得
		DirectX::Mouse::ButtonStateTracker button = *LibrarySingleton::GetInstance()->GetButtonStateTracker();
		
		//		スペースまたはマウス左クリックを押した場合
		if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
			button.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			//		ゲームを終了する
			PostQuitMessage(0);
		}
	}
	else
	{
		//		状態を選択する
		if (m_titleSelectManager->GetInformation()->GetDirection())
		{
			//		設定選択状態にする
			m_titleSelectManager->ChangeState(TitleInformation::State::PlayState);
		}
		else
		{
			//		終了選択状態にする
			m_titleSelectManager->ChangeState(TitleInformation::State::SettingState);
		}
	}

}
