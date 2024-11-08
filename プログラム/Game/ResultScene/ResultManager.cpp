/*
* @file		ResultManager.cpp
* @brief	リザルトマネージャー
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultManager.h"

#include "State/ResultStart.h"
#include "State/ResultNumberMove.h"
#include "State/ResultEvaluation.h"
#include "State/ResultStay.h"
#include "State/ResultEnd.h"

ResultManager::ResultManager()
	:
	m_score(0),
	m_time(0),
	m_deathCount(0),
	m_iState(),
	m_rotation(0.0f),
	m_state{},
	m_menuUseJudgement(false)
{
	Generation();
}

ResultManager::~ResultManager()
{
}

void ResultManager::Initialize(int score, int time, int deathCount)
{
	m_score = score;
	m_time = time;
	m_deathCount = deathCount;

	//		数字上昇シェーダーの初期化
	m_riseNumber->Initialize(m_deathCount, m_time, m_score);

	//		スクリーンエフェクトの初期化
	m_screenEffectManager->Initialize();

	//		プレイヤーのアニメーション初期化
	m_playerAnimation->Initialize();

	//		スタンダードシェーダーの作製
	CreateStandardShader();

	//		背景の初期化
	m_backGroundMove->Initialize();

	//--
	//	フェード初期処理
	//--

	//		フェード描画の作製
	m_fade = std::make_unique<UIRenderManager>();

	//		バッファ
	ResultInformation::ConstBuffer buffer = m_information->GetBuffer();

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

	//		初期化
	m_information->Initialize(m_shader.get(), m_riseNumber.get(),
		m_fade.get(), m_backGroundMove.get(),
		m_screenEffectManager.get(),
		m_playerAnimation.get());

	//		初期状態を代入する
	m_state = State::Start;

	//		初期状態を設定する
	m_iState = m_stateInformation[m_state].get();

	//		状態を初期化する
	m_iState->Initialize();
}

void ResultManager::Generation()
{
	//		背景の生成
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		数字上昇シェーダーの生成
	m_riseNumber = std::make_unique<RiseNumberShader>();

	//		プレイヤーのアニメーションの作製
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Result);

	//		スクリーンエフェクトマネージャーの作製
	m_screenEffectManager = std::make_unique<ScreenEffectManager>(ScreenEffectManager::ResultScene, nullptr);

	//		情報を生成する
	m_information = std::make_unique<ResultInformation>();

	//		状態を作成する
	CreateState();
}

void ResultManager::Update()
{
	//		状態の更新
	m_iState->Update();

	//		プレイヤーの回転
	m_rotation += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->PLAYER_ROTATION_SPEED;

	//		プレイヤーのアニメーション
	m_information->GetAnimation()->Execute(0.0f, {3.9f, 1.1f, 8.0f},
		{m_rotation + 180.0f, 0.0f}, m_information->PLAYER_HEIGHT);
}

void ResultManager::Render()
{
	//		レンダーターゲットの変更
	m_information->GetScreenEffect()->ChangeRenderTarget();

	//		プレイヤーの描画(ワイヤー)
	m_information->GetAnimation()->Render();

	//		レンダーターゲットを戻す
	m_information->GetScreenEffect()->FirstRenderTarget();

	//		移動背景の描画
	m_information->GetBackGround()->Render();

	//		背景の描画(UI)
	m_information->GetStandardShader()->Render(ResultInformation::ResultUIType::Back);

	//		プレイヤの背景
	m_information->GetStandardShader()->Render(ResultInformation::ResultUIType::PlayerBack);

	//		レンダーターゲットの描画
	m_information->GetScreenEffect()->Render();

	//		状態の描画
	m_iState->Render();
}

void ResultManager::Finalize()
{
	m_information->GetRiseNumber();

	m_information->Finalize();

	m_riseNumber->Finalize();

	m_backGroundMove->Finalize();

	m_playerAnimation->Finalize();

	m_screenEffectManager->Finalize();

	m_shader.reset();

	m_fade.reset();

	m_rotation = 0.0f;
}

void ResultManager::CreateState()
{
	//		状態を生成する
	m_stateInformation.insert({State::Start, std::make_unique<ResultStart>(this)});
	m_stateInformation.insert({ State::NumberMove, std::make_unique<ResultNumberMove>(this) });
	m_stateInformation.insert({ State::Evaluation, std::make_unique<ResultEvaluation>(this) });
	m_stateInformation.insert({ State::Stay, std::make_unique<ResultStay>(this) });
	m_stateInformation.insert({ State::End, std::make_unique<ResultEnd>(this) });
}

void ResultManager::AnimationSkip()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		マウスの取得
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Spaceまたは左クリックを押した場合復活する
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		状態を切り替える(待機状態)
		m_iState = m_stateInformation[State::Stay].get();
	}
}

void ResultManager::CreateStandardShader()
{
	//		リザルトUIマネージャーの生成
	m_shader = std::make_unique<StandardShader<ResultInformation::ResultUIType>>();

	//		初期化処理
	m_shader->Initialize();

	//		背景画像
	m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ResultBack.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f },
		ResultInformation::ResultUIType::Back);

	//		スコアによって評価を変える
	if (m_information->SCORE_A < m_score)
	{
		//		A評価の生成
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreA.png",
			m_information->SCORE_POSITION, { 0.0f, 0.0f },
			ResultInformation::ResultUIType::EvaluationUI);
	}
	else if (m_information->SCORE_B < m_score)
	{
		//		B評価の生成
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreB.png",
			m_information->SCORE_POSITION, { 0.0f, 0.0f },
			ResultInformation::ResultUIType::EvaluationUI);
	}
	else
	{
		//		C評価の生成
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreC.png",
			m_information->SCORE_POSITION, { 0.0f, 0.0f },
			ResultInformation::ResultUIType::EvaluationUI);
	}

	//		次のシーン誘導の生成
	m_shader->CreateUIInformation(L"Resources/Texture/UI/GameOver/button.png",
		m_information->NEXT_SCENE, { 1.0f, 1.0f },
		ResultInformation::ResultUIType::Button);

	//		プレイヤの背景の生成
	m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/PlayerBack.png",
		{-300.0f, -100.0f}, {1.0f, 1.0f},
		ResultInformation::ResultUIType::PlayerBack);
}

void ResultManager::BackGroundUpdate()
{
	//		背景の更新
	m_information->GetBackGround()->Update();
}

void ResultManager::ChangeState(State state)
{
	//		同じ状態なら処理をしない
	if (m_state == state) return;

	//		現在の状態の終了処理をする
	m_iState->Finalize();

	m_state = state;

	//		状態を切り替える
	m_iState = m_stateInformation[state].get();

	//		新しい状態の初期化処理をする
	m_iState->Initialize();
}
