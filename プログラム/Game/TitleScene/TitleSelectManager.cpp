/*
* @file		BackGroundMove.cpp
* @brief	タイトルの選択マネージャー
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "TitleSelectManager.h"

#include "State/SelectPlayState.h"
#include "State/SelectEndState.h"
#include "State/SelectSettingState.h"
#include "State/ChangeSceneState.h"
#include "State/StartSceneState.h"

TitleSelectManager::TitleSelectManager()
	:
	m_iState(),
	m_state{},
	m_menuInformation(nullptr)
{
	Generation();
}

TitleSelectManager::~TitleSelectManager()
{
}

void TitleSelectManager::Initialize()
{
	//		マウスのフォールチをリセットする
	DirectX::Mouse::Get().ResetScrollWheelValue();

	//		スタンダードシェーダーの作製
	CreateStandardShader();

	//		情報の初期化
	m_information->Initilaize(m_backGroundMove.get(), m_standardShader.get(),
		m_fade.get());

	//		背景の初期化
	m_backGroundMove->Initialize();

	//		スクリーンエフェクトの初期化
	m_screenEffectManager->Initialize();

	//		プレイヤーのアニメーション初期化
	m_playerAnimation->Initialize();

	//----
	//		タイトルの状態の作製
	//---

	//		初期の状態
	m_state = TitleInformation::State::StartState;
	
	m_iState = (*m_information->GetStateInformation())[m_state].get();

	//		初期化する
	m_iState->Initialize();
}

void TitleSelectManager::Generation()
{
	//		タイトル情報を設定する
	m_information = std::make_unique<TitleInformation>();

	//		背景の生成
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		タイトル共通処理の生成
	m_commonProcess = std::make_unique<TitleCommonProcess>(m_information.get());

	//		プレイヤーのアニメーションの作製
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Title);

	//		スクリーンエフェクトマネージャーの作製
	m_screenEffectManager = std::make_unique<ScreenEffectManager>(ScreenEffectManager::ResultScene, nullptr);

	//----
	//		フェードインアウトの初期化
	//---

	TitleInformation::ConstBuffer buffer = m_information->GetBuffer();

	//		フェード描画の作製
	m_fade = std::make_unique<UIRenderManager>();

	//		フェードの作成
	m_fade->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		L"Resources/Shader/UI/FadeShader/FadeUIVS.cso",
		L"Resources/Shader/UI/FadeShader/FadeUIGS.cso",
		L"Resources/Shader/UI/FadeShader/FadeUIPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	buffer.rotationMatrix = m_fade->GetRotationMatrix();

	m_information->SetBuffer(buffer);

	//----
	//		タイトルの状態の作製
	//---

	auto stateInformation = m_information->GetStateInformation();

	//		状態の情報を設定する
	(*stateInformation).insert({ TitleInformation::State::PlayState, std::make_unique<SelectPlayState>(this) });
	(*stateInformation).insert({ TitleInformation::State::EndState, std::make_unique<SelectEndState>(this) });
	(*stateInformation).insert({ TitleInformation::State::SettingState, std::make_unique<SelectSettingState>(this) });
	(*stateInformation).insert({ TitleInformation::State::StartState, std::make_unique<StartSceneState>(this) });
	(*stateInformation).insert({ TitleInformation::State::ChangState, std::make_unique<ChangeSceneState>(this) });

	//		描画順を設定する
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::Play);
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::Setting);
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::End);
}

void TitleSelectManager::Update()
{
	//		背景の更新処理
	m_backGroundMove->Update();

	//		メニューを開いている場合は処理をしない
	if (m_menuInformation->GetMenuJudgement()) return;

	//		プレイヤーのアニメーション
	m_playerAnimation->Execute(0.0f, { 0.5f, -2.0f, 1.05f },
		{ 180.0f, 0.0f }, 2.5f);

	//		更新処理
	m_iState->Update();
}

void TitleSelectManager::Render()
{
	m_screenEffectManager->ChangeRenderTarget();

	m_playerAnimation->Render();

	m_screenEffectManager->FirstRenderTarget();

	//		背景の描画
	m_backGroundMove->Render();

	//		レンダーターゲットの描画
	m_screenEffectManager->Render();

	//		選択の描画
	for (int i = 0, max = static_cast<int>((*m_information->GetDraowOder()).size()); i < max; ++i)
	{
		//		選択UIの描画
		m_information->GetStandardShader()->Render((*m_information->GetDraowOder())[i]);
	}

	//		スペース
	m_standardShader->Render(TitleInformation::TitleUIType::Space);

	//		タイトルロゴの描画
	m_standardShader->Render(TitleInformation::TitleUIType::TitleRogo);

	//		描画処理
	m_iState->Render();
}

void TitleSelectManager::Finalize()
{
	//		情報の初期化
	m_information->Finalize();

	m_playerAnimation->Finalize();

	m_screenEffectManager->Finalize();

	m_backGroundMove->Finalize();

	m_standardShader.reset();
}

void TitleSelectManager::InputKey()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		WボタンORマウスホイール上で上に移動
	if (keyboard.IsKeyPressed(DirectX::Keyboard::S)|| 
		m_information->GetScrollWheel() > DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		もし移動処理をしている場合は処理をしない
		if (!m_information->GetKeyInput())
		{
			//		キーを押している
			m_information->SetKeyInput(true);
			//		移動する向き（上）
			m_information->SetDirection(true);

			//		選択効果音
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		m_information->SetScrollWheel(DirectX::Mouse::Get().GetState().scrollWheelValue);
	}

	//		SボタンORマウスホイールしたで下に移動
	if (keyboard.IsKeyPressed(DirectX::Keyboard::W) ||
		m_information->GetScrollWheel() < DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		もし移動処理をしている場合は処理をしない
		if (!m_information->GetKeyInput())
		{
			//		キーを押している
			m_information->SetKeyInput(true);
			//		移動する向き（下）
			m_information->SetDirection(false);

			//		選択効果音
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		//		ホイールの値を更新する
		m_information->SetScrollWheel(DirectX::Mouse::Get().GetState().scrollWheelValue);
	}
}

void TitleSelectManager::CreateStandardShader()
{
	//		タイトルUIマネージャーの生成
	m_standardShader = std::make_unique<StandardShader<TitleInformation::TitleUIType>>();

	//		タイトルUIマネージャの初期化
	m_standardShader->Initialize();

	//		タイトルロゴの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/TitleRogo.png",
		m_information->TITLE_POINT, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::TitleRogo);

	//		Playの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		m_information->CENTER_POINT, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::Play);

	//		Endの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		m_information->UP_POINT , { m_information->MIN_SCALE,
		 m_information->MIN_SCALE },
		TitleInformation::TitleUIType::End);

	//		Settingの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		m_information->UNDER_POINT, { m_information->MIN_SCALE,
		 m_information->MIN_SCALE },
		TitleInformation::TitleUIType::Setting);

	//		Spaceの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/Space.png",
		m_information->SPACE_PLAY, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::Space);

	//		Wの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/W.png",
		m_information->W_END, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::W);

	//		Aの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/A.png",
		m_information->A_SETTING, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::A);
}

void TitleSelectManager::ChangeState
(TitleInformation::State state)
{
	//		同じ状態なら処理をしない
	if (m_state == state) return;

	//		現在の状態の終了処理をする
	m_iState->Finalize();

	//		状態を切り替える
	m_state = state;

	//		状態を切り替える
	//m_iState = m_stateInformation[m_state].get();
	m_iState = (*m_information->GetStateInformation())[m_state].get();

	//		新しい状態の初期化処理をする
	m_iState->Initialize();
}