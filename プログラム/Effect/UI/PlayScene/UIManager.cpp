/*
* @file		UIManager.cpp
* @brief	UIマネージャー
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "UIManager.h"

#include "Clock/ClockManager.h"
#include "CoolTime/CoolTime.h"
#include "Effect/UI/PlayScene/GameOver/GameOverManager.h"
#include "Effect/UI/PlayScene/GameClear/GameClearManager.h"
#include "Effect/UI/PlayScene/SpeedLine/SpeedLine.h"
#include "Effect/UI/PlayScene/GameStart/GameStart.h"
#include "Effect/UI/PlayScene/CountDown/CountDown.h"

UIManager::UIManager(PlayerInformation* playerInformation,
					 GameManager* gameManager)
	:
	m_playerInformation(playerInformation),
	m_gameManager(gameManager)
{
	Generation();
}

UIManager::~UIManager()
{
}

void UIManager::Initialize()
{
	//		スタンダードシェーダーの作製
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		スタンダードシェーダーの初期化
	m_standardShader->Initialize();

	//		UIテクスチャの作製
	CreateStandardUITexture();

	//		時計の背景の初期化
	m_clockManager->Initialize();

	//		クールタイムの初期化
	m_coolTime->Initialize();

	//		ゲームオーバーの初期化
	m_gameOver->Initialize();

	//		初期化処理
	m_speedLine->Initialize();

	//		ゲームクリアマネージャーの初期化
	m_clearManager->Initialize();

	//		ゲームスタートの初期化
	m_gameStart->Initialize();

	//		カウントダウンの初期化処理
	m_countDonw->Initialize();
}

void UIManager::Generation()
{
	//		クールタイムの生成
	m_coolTime = std::make_unique<CoolTime>(this);

	//		時計の背景の生成
	m_clockManager = std::make_unique<ClockManager>(this);

	//		ゲームーオーバーの生成
	m_gameOver = std::make_unique<GameOverManager>(m_gameManager, this);

	//		ゲームクリアマネージャーの生成
	m_clearManager = std::make_unique<GameClearManager>(m_gameManager, this);

	//		ゲームスタートの生成
	m_gameStart = std::make_unique<GameStart>(m_gameManager, this);

	//		スピードラインの生成
	m_speedLine = std::make_unique<SpeedLine>(this);

	//		カウントダウンの生成
	m_countDonw = std::make_unique<CountDown>();
}

void UIManager::Update()
{
	//		速度の更新処理
	m_speedLine->Update();

	//		時間の更新
	m_clockManager->Update(m_gameManager);

	//		ダッシュクールタイムの更新
	m_coolTime->Update(m_playerInformation);

	//		ゲームオーバーの更新
	m_gameOver->Update();

	//		ゲームクリアマネージャーの更新
	m_clearManager->Update();

	//		ゲームスタートマネージャーの更新
	m_gameStart->Update();

	//		カウントダウンの更新処理
	m_countDonw->Update(m_gameManager->GetLimitTime() - m_clockManager->GetElapsedTime());
}

void UIManager::Finalize()
{
	m_standardShader.reset();

	m_clockManager->Finalize();

	m_coolTime->Finalize();

	m_gameOver->Finalize();

	m_speedLine->Finalize();

	m_clearManager->Finalize();

	m_gameStart->Finalize();

	m_countDonw->Finalize();
}

void UIManager::FrontRender()
{
	//		スピードラインの描画
	m_speedLine->Render();

	//		時計の描画
	m_clockManager->Render();

	//		ダッシュクールタイムの描画
	m_coolTime->Render();

	//		スクリーンの線の描画
	m_standardShader->Render(UIType::ScreenRay);

	//		ゲームクリアマネージャーの描画
	m_clearManager->Render();
}

void UIManager::BackRender()
{
	//		カウントダウン
	m_countDonw->Render();

	//		ゲームーバーの描画
	m_gameOver->Render();

	//		ゲームスタートの描画
	m_gameStart->Render();
}

void UIManager::CreateStandardUITexture()
{
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/Clock/ClockBackGround.png", CLOCK_BACK_GROUND_POSITION, { 0.8f, 0.8f }, UIType::ClockBackGround);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/Clock/ClockColon.png", CLOCK_BACK_GROUND_POSITION, { 0.8f, 0.8f }, UIType::ClockColon);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/CoolTime/CoolTimeBack.png", CLOCK_BACK_TIME_GROUND_POSITION, { 0.6f, 0.6f }, UIType::CloolTimeBackGround);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameOver/GameOver.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameOver);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameOver/Continue.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameOverContinue);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameOver/button.png", NEXT_INDCCTION, { 0.6f, 0.6f }, UIType::NextInduction);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/ScreenRay/ScreenRay.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::ScreenRay);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png", MESSAGE_BER_UP, { 0.0f, 1.0f }, UIType::GameClearBarUp);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png", MESSAGE_BER_DOWN, { 0.0f, 1.0f }, UIType::GameClearBarUnder);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBack.png", { 0.0f, 0.0f }, { 1.0f, 0.0f }, UIType::GameClearBackGround);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameStart/TimeLimit.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameStartTimeLimit);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameStart/Ten.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameStartTimeTen);
}
