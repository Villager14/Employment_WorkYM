/*
* @file		MenuCommonProcess.cpp
* @brief	メニューの共通処理
* @author	Morita
* @date		2024/08/05
*/

#include "pch.h"

#include "MenuCommonProcess.h"

MenuCommonProcess::MenuCommonProcess(MenuInformation* menuInformation)
	:
	m_information(menuInformation)
{
}

MenuCommonProcess::~MenuCommonProcess()
{
}

bool MenuCommonProcess::MenuEscCloseProcess()
{
	//		ESCキーを押した場合
	if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()
		->IsKeyPressed(DirectX::Keyboard::Tab))
	{
		return true;
	}

	return false;
}

bool MenuCommonProcess::BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max)
{
	DirectX::SimpleMath::Vector2 mousePosition;

	mousePosition.x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	mousePosition.y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	//		範囲内にマウスがあるかどうか
	if (min.x <= mousePosition.x && max.x >= mousePosition.x &&
		min.y <= mousePosition.y && max.y >= mousePosition.y)
	{
		//		範囲内
		return true;
	}

	//		範囲外
	return false;
}

bool MenuCommonProcess::ButtonCollider(MenuInformation::MenuType type)
{
	MenuInformation::MenuType hitType = MenuInformation::MenuType::Empty;

	//		範囲内にいるかどうかのフラグ
	bool hitJudgement = false;

	//		Audioの大まかボタン内にいるか？
	if (BoxCollider(m_information->AUDIO_TITLE_POSITION_MIN, m_information->AUDIO_TITLE_POSITION_MAX))
	{
		//		範囲内にいるUIをAudioにする
		m_information->SetRangeUI(AboveUI::AudioSelect);

		//		範囲内にいる
		hitJudgement = true;

		//		範囲にいるものが現在の状態でなければ処理をする
		if (MenuInformation::MenuType::Audio != type)
			hitType = MenuInformation::MenuType::Audio;
	}

	//		Optionの大まかなボタン内にいるか？
	if (BoxCollider(m_information->OPTION_TITLE_POSITION_MIN, m_information->OPTION_TITLE_POSITION_MAX))
	{
		//		範囲内にいるUIをOptionにする
		m_information->SetRangeUI(AboveUI::OptionSelect);

		//		範囲内にいる
		hitJudgement = true;

		//		範囲にいるものが現在の状態でなければ処理をする
		if (MenuInformation::MenuType::Option != type)
			hitType = MenuInformation::MenuType::Option;
	}

	//		Backの大まかなボタンの中にいるか？
	if (BoxCollider(m_information->GAMEPLAY_TITLE_POSITION_MIN, m_information->GAMEPLAY_TITLE_POSITION_MAX))
	{
		//		範囲内にいるUIをGamePlayにする
		m_information->SetRangeUI(AboveUI::GamePlaySelect);

		//		範囲内にいる
		hitJudgement = true;

		//		範囲にいるものが現在の状態でなければ処理をする
		if (MenuInformation::MenuType::GamePlay != type)
			hitType = MenuInformation::MenuType::GamePlay;
	}

	//		範囲内にいない場合
	if (!hitJudgement)
	{
		//		選択していない状態にする
		m_information->SetRangeUI(AboveUI::Empty);

		//		時間のリセット
		m_information->GetMenuSelect()->TimeReset();
	}

	//		当たっていない場合これ以上処理をしない
	if (hitType == MenuInformation::MenuType::Empty) return false;

	//		範囲内でクリックした場合
	if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
		== DirectX::Mouse::ButtonStateTracker().PRESSED)
	{
		//		クリックした状態を代入する
		m_information->SetSelectUI(hitType);

		MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

		return true;
	}

	return false;
}

void MenuCommonProcess::SlideProcess(AboveUI::UIType type)
{
	//		現在の座標
	DirectX::SimpleMath::Vector2 nowPosition = (*m_information->GetAboveUI()->GetInformation())[type].position;

	//		中心座標
	nowPosition += {  LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f,
		LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f };

	DirectX::SimpleMath::Vector2 max = nowPosition + m_information->KNOB_LENGTH;
	DirectX::SimpleMath::Vector2 min = nowPosition - m_information->KNOB_LENGTH;

	//		四角の当たり判定
	if (BoxCollider(min, max))
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			m_information->SetSliderSelectUI(type);
		}
	}

	if (m_information->GetSliderSelectUI() == type)
	{
		(*m_information->GetAboveUI()->GetInformation())[type].position.x = static_cast<float>
			(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x) - 640.0f;

		(*m_information->GetAboveUI()->GetInformation())[type].position.x = Library::Clamp
		((*m_information->GetAboveUI()->GetInformation())[type].position.x,
			-81.0f, 480.0f);


		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().RELEASED)
		{
			//		効果音の場合のみ離したとき効果音を鳴らす
			if (m_information->GetSliderSelectUI() == AboveUI::UIType::SoundEffectKnob)
				MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

			m_information->SetSliderSelectUI(AboveUI::UIType::Empty);

		}
	}

}

void MenuCommonProcess::MousePointa()
{
	//		マウスの座標
	DirectX::SimpleMath::Vector2 mousePosition;

	//		マウスの現在座標を受け取る
	mousePosition.x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x) - LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f;
	mousePosition.y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y) - LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f;

	//		マウスポインタのUIの座標を設定する
	(*m_information->GetStandardShader()->GetUIInformation())[MenuInformation::UIType::MousePointa].position = mousePosition;

	//		マウスポインタの描画
	m_information->GetStandardShader()->Render(MenuInformation::UIType::MousePointa);
}
