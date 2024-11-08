/*
* @file		SelectSettingState.cpp
* @brief	設定を選択した状態
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
	//		キー入力処理
	m_titleSelectManager->InputKey();
	
	//		UIの移動処理
	UIMove();

	//		シーン切り替え処理
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
	//		キー処理がなかった場合処理をしない
	if (!m_titleSelectManager->GetInformation()->GetKeyInput()) return;

	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetInformation()->MOVE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		キー
	float key = m_time;//1.0f - pow(1.0f - m_time, 4.0f);

	//		上に移動
	if (m_titleSelectManager->GetInformation()->GetDirection())
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
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_SETTING,
				m_titleSelectManager->GetInformation()->SPACE_END, key);
	
		/*
		//		W座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_PLAY,
				m_titleSelectManager->GetInformation()->W_SETTING, key);

		//		A座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_END,
				m_titleSelectManager->GetInformation()->A_PLAY, key);
				*/
	}
	//		下に移動
	else
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
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->SPACE_SETTING,
				m_titleSelectManager->GetInformation()->SPACE_PLAY, key);
	
		/*
		//		W座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::W].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->W_PLAY,
				m_titleSelectManager->GetInformation()->W_END, key);
	
		//		A座標の遷移
		(*m_titleSelectManager->GetInformation()->GetStandardShader()->GetUIInformation())
			[TitleInformation::TitleUIType::A].position =
			DirectX::SimpleMath::Vector2::Lerp(m_titleSelectManager->GetInformation()->A_END,
				m_titleSelectManager->GetInformation()->A_SETTING, key);
		*/
	}
}

void SelectSettingState::ChangeSceneProcess()
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
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

			//		メニューを開く
			m_titleSelectManager->GetMenuInformation()->SetMenuJudgement(true);
		}
	}
	else
	{

		if (m_titleSelectManager->GetInformation()->GetDirection())
		{
			//		設定選択状態にする
			m_titleSelectManager->ChangeState(TitleInformation::State::EndState);
		}
		else
		{
			//		終了選択状態にする
			m_titleSelectManager->ChangeState(TitleInformation::State::PlayState);
		}
	}
}
