/*
* @file		MenuManager.cpp
* @brief	メニューのマネージャー
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuManager.h"

#include <Windows.h>

#include "Effect/UI/Menu/AboveUI/AboveUI.h"
#include "Effect/UI/Menu/Slider/Slider.h"
#include "Effect/UI/Menu/MenuSelect/MenuSelect.h"
#include "Effect/UI/Menu/FrameWalkUI/FrameWalkUI.h"


MenuManager::MenuManager(SceneManager* sceneManager)
	:
	m_state(),
	m_type{},
	m_firstAudioMenuJudgement(true),
	m_sceneManager(sceneManager)
{
	//		状態の生成
	m_menuStateInformation.insert({ MenuInformation::Start, std::make_unique<MenuStart>(this) });
	m_menuStateInformation.insert({ MenuInformation::Audio, std::make_unique<AudioSetting>(this) });
	m_menuStateInformation.insert({ MenuInformation::Option, std::make_unique<OptionSetting>(this) });
	m_menuStateInformation.insert({ MenuInformation::GamePlay, std::make_unique<EndSetting>(this) });
	m_menuStateInformation.insert({ MenuInformation::Close, std::make_unique<MenuClose>(this) });

	//		UIを作成する
	CreateUI();

	m_commonProcess = std::make_unique<MenuCommonProcess>(m_information.get());
}

MenuManager::~MenuManager()
{
}

void MenuManager::Initialize()
{

	m_type = MenuInformation::Start;

	//		初期の状態
	m_state = m_menuStateInformation[m_type].get();

	//		初期化処理
	m_state->Initialize();

		//		マウスを相対位置にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);
}

void MenuManager::Update()
{
	//		メニューを使用することができるかどうか
	if (!m_information->GetMenuUseJudgement()) return;

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	if (keyboard.IsKeyPressed(DirectX::Keyboard::Tab))
	{
		ShowCursor(FALSE);

		m_information->SetMenuJudgement(true);
	}

	//		メニューを使用するかどうか
	if (!m_information->GetMenuJudgement()) return;

	//		初期化処理を行うかどうか
	if (m_information->GetInitializeJudgement())
	{
		Initialize();

		m_information->SetInitializeJudgement(false);
	}

	//		更新処理
	m_state->Update();

	//		メニューモードを終了したとき
	if (!m_information->GetMenuJudgement())
	{
		//		マウス相対モード
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

		Finalize();
	}
}

void MenuManager::Render()
{
	//		メニューを使用しているかどうか
	if (!m_information->GetMenuJudgement()) return;

	//		描画処理
	m_state->Render();

	//		デバックフォント
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionX",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x), 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionY",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y), 0, 30);
	LibrarySingleton::GetInstance()->DebugFont(L"HitJudgement",
		m_commonProcess->BoxCollider(m_information->GAMEPLAY_TITLE_POSITION_MIN, m_information->GAMEPLAY_TITLE_POSITION_MAX), 0, 60);
}

void MenuManager::Finalize()
{
	m_information->SetInitializeJudgement(true);
}

void MenuManager::MenuBackRneder()
{
	//		背景の描画
	m_information->GetStandardShader()->Render(MenuInformation::UIType::BackGround);

	//		バー１の描画
	m_information->GetStandardShader()->Render(MenuInformation::UIType::Bar1);

	//		バー２の描画
	m_information->GetStandardShader()->Render(MenuInformation::UIType::Bar2);
}

void MenuManager::CreateUI()
{
	//		スタンダードシェーダーの生成
	m_standardShader = std::make_unique<StandardShader<MenuInformation::UIType>>();

	//		スタンダードシェーダーの初期化処理
	m_standardShader->Initialize();

	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, 13.0f }, { 0.0f, 1.0f }, MenuInformation::UIType::Bar1);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, -13.0f }, { 0.0f, 1.0f }, MenuInformation::UIType::Bar2);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBack.png",
		{ 0.0f, 0.0f }, { 0.0f, 1.0f }, MenuInformation::UIType::BackGround);
	m_standardShader->CreateUIInformation(L"Resources/Texture/Menu/Title/mousePointa.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f }, MenuInformation::UIType::MousePointa);

	//		上昇UIの生成
	m_aboveUI = std::make_unique<AboveUI>();

	//		上昇UIの初期化
	m_aboveUI->Initialize();

	//		スライダーUIの生成
	m_slider = std::make_unique<Slider>();

	//		スライダーUIの初期化
	m_slider->Initialize();

	//		メニュー選択UIの生成
	m_menuSelect = std::make_unique<MenuSelect>();

	//		メニュー選択UIの初期化
	m_menuSelect->Initialize();

	//		フレームワークを生成する
	m_frameWalkUI = std::make_unique<FrameWalkUI>();

	//		フレームワークを生成する
	m_frameWalkUI->Initialize();

	//		メニューの情報を生成する
	m_information = std::make_unique<MenuInformation>();

	//		メニューの情報を初期化する
	m_information->Initialzie(m_standardShader.get(),
		m_aboveUI.get(), m_slider.get(), m_menuSelect.get(), m_frameWalkUI.get());

}

void MenuManager::RoughMenuViwe(float transitionTime)
{
	//		Opetionの描画
	m_information->GetAboveUI()->Render(AboveUI::UIType::OptionSelect, transitionTime);

	//		GamePlayの描画
	m_information->GetAboveUI()->Render(AboveUI::UIType::GamePlaySelect, transitionTime);

	//		Audioのタイトル描画
	m_information->GetAboveUI()->Render(AboveUI::UIType::AudioSelect, transitionTime);
}

void MenuManager::MenuSelectView()
{
	//		選択していない場合描画処理をしない
	if (m_information->GetRangeUI() != AboveUI::UIType::Empty)
		m_information->GetMenuSelect()->Render((*m_information->GetAboveUI()->GetInformation())[m_information->GetRangeUI()].position);
}

void MenuManager::ChangState(MenuInformation::MenuType type)
{
	//		同じタイプの場合処理をしない
	if (m_type == type) return;

	//		終了処理
	m_state->Finalize();

	//		タイプの更新
	m_type = type;

	//		状態の更新
	m_state = m_menuStateInformation[type].get();

	//		初期化処理
	m_state->Initialize();
}

bool MenuManager::Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
							bool* startJudgement, bool endJudgement, bool moveJudgement)
{
	//		開始状態の場合
	if (*startJudgement)
	{
		//		時間1の更新
		*transitionTime1 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

		//		時間1が一定時間以上になったら他の時間も更新する
		if (*transitionTime1 > 0.3f)
		{
			//		時間2の更新
			*transitionTime2 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

			//		時間2が一定時間以上3遷移フラグがオンの場合時間3の更新をする
			if (*transitionTime2 > 0.3f && moveJudgement)
			{
				//		時間3の更新
				*transitionTime3 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;
			}
		}

		//		1以上にならないようにする
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		//		3の更新をする場合
		if (moveJudgement)
		{
			//		3の更新が終わったら
			if (*transitionTime3 >= 1.0f)
			{
				//		開始状態を終了する
				*startJudgement = false;
			}
		}
		else
		{
			//		2の更新が終わったら
			if (*transitionTime2 >= 1.0f)
			{
				//		開始状態を終了する
				*startJudgement = false;
			}
		}

		return true;
	}

	//		終了状態の場合
	if (endJudgement)
	{
		//		時間1の更新
		*transitionTime1 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

		//		時間1が一定時間以下になったら他の時間も更新する
		if (*transitionTime1 < 0.7f)
		{
			//		時間2の更新
			*transitionTime2 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

			//		時間2が一定時間以下3遷移フラグがオンの場合時間3の更新をする
			if (*transitionTime2 < 0.7f && moveJudgement)
			{
				//		時間3の更新
				*transitionTime3 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;
			}
		}

		//		0以下にならないようにする
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		if (moveJudgement)
		{
			if (*transitionTime3 <= 0.0f)
			{
				//		シーンを切り替える
				ChangState(MenuInformation::MenuType::Close);
			}
		}
		else
		{
			if (*transitionTime2 <= 0.0f)
			{
				//		シーンを切り替える
				ChangState(m_information->GetSelectUI());
			}
		}

		return true;
	}

	return false;
}
