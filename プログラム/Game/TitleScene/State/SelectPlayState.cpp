/*
* @file		SelectPlayerState.cpp
* @brief	プレイを選択した状態
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
	//		キー入力処理
	m_titleSelectManager->InputKey();

	//		UIの移動処理
	UIMove();

	//		シーン切り替え処理
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
	//		キー処理がなかった場合処理をしない
	if (!m_titleSelectManager->GetInformation()->GetKeyInput()) return;

	//		経過時k菜
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetInformation()->MOVE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		キー
	float key = sqrt(1.0f - pow(m_time - 1.0f, 2.0f));

	//		上に移動
	if (m_titleSelectManager->GetInformation()->GetDirection())
	{
		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::UP,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Play);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Down,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::Setting);

		m_titleSelectManager->GetCommonProcess()->MoveProcess(m_titleSelectManager->GetInformation()->MoveDirection::Back,
			m_titleSelectManager->GetInformation()->GetDirection(), m_time, TitleInformation::TitleUIType::End);
	
		//		Space座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::Space].position =
		DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_PLAY,
			m_titleSelectManager->GetInformation()->SPACE_SETTING, key);

		/*
		//		W座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position = 
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_END,
				m_titleSelectManager->GetInformation()->W_PLAY, key);

		//		A座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_SETTING,
				m_titleSelectManager->GetInformation()->A_END, key);
		*/
	}
	//		下に移動
	else
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
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_PLAY,
				m_titleSelectManager->GetInformation()->SPACE_END, key);
	
		/*
		//		W座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_END,
				m_titleSelectManager->GetInformation()->W_SETTING, key);

		//		A座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_SETTING,
				m_titleSelectManager->GetInformation()->A_PLAY, key);
		*/
	}
}

void SelectPlayState::ChangeSceneProcess()
{
	//		時間が１以下の場合処理をしない
	if (m_time < 1.0f)
	{
		//		キーボードの取得
		DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

		//		ボタンの取得
		DirectX::Mouse::ButtonStateTracker button = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

		if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
			button.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			//		終了選択状態にする
			m_titleSelectManager->ChangeState(TitleInformation::State::ChangState);
		}
	}
	else
	{

		//		移動方向によって状態を切り替える
		if (!m_titleSelectManager->GetInformation()->GetDirection())
		{
			//		終了選択状態にする
			m_titleSelectManager->ChangeState(TitleInformation::State::EndState);
		}
		else
		{
			//		設定選択状態にする
			m_titleSelectManager->ChangeState(TitleInformation::State::SettingState);
		}
	}
}
