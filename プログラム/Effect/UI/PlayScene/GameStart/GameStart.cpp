/*
* @file		GameStart.cpp
* @brief	ゲームスタートマネージャー
* @author	Morita
* @date		2024/10/20
*/

#include "pch.h"

#include "GameStart.h"

GameStart::GameStart(GameManager* gameManager, UIManager* uiManager)
	:
	m_gameManager(gameManager),
	m_uiManager(uiManager),
	m_elapsedTime(0.0f),
	m_stayTime(0.0f),
	m_numberUpdateFrequency(0.0f),
	m_numberElapsedTime(0.0f),
	m_limitTime(0.0f),
	m_limitJudgement(false),
	m_numberTime(0.0f),
	m_numberStayTime(0.0f),
	m_threeCountNumber(3),
	m_threeCountElapsedTime(0.0f),
	m_endJudgement(false),
	m_numberSizeTime(0.0f)
{
}

GameStart::~GameStart()
{
}

void GameStart::Initialize()
{
	m_stayTime = 0.0f;
	m_elapsedTime = 0.0f;
	m_numberUpdateFrequency = 0.0f;
	m_numberElapsedTime = 0.0f;
	m_threeCountNumber = 3;
	m_threeCountElapsedTime = 0.0f;
	m_endJudgement = false;
	m_limitJudgement = false;
	m_numberSizeTime = 0.0;
	m_numberStayTime = 0.0f;
	m_numberTime = 0.0f;

	m_limitTime = m_gameManager->GetLimitTime();

	m_numberRender = std::make_unique<UIRenderManager>();

	//		数字シェーダーの作製
	m_numberRender->Create(L"Resources/Texture/UI/GameStart/number.png",
		L"Resources/Shader/UI/Number/NumberVS.cso",
		L"Resources/Shader/UI/Number/NumberGS.cso",
		L"Resources/Shader/UI/Number/NumberPS.cso",
		m_constBuffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		ウィンドウサイズを設定する
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
}

void GameStart::Update()
{
	if (m_endJudgement) return;

	if (!m_gameManager->FlagJudgement(GameManager::StartLimitView)) return;

	//		初手の待機時間
	if (m_stayTime < 0.5f)
	{
		m_stayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		return;
	}

	//		タイムりリミットの移動処理
	if (TimeLimitMove()) return;

	//		タイムリミットタイムランダム処理
	if (TimeLimitNumberRandom()) return;

	//		番号サイズ時間処理
	if (NumberSizeTime()) return;

	//		待機時間
	if (m_numberStayTime < 0.5f)
	{
		m_numberStayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		return;
	}

	//		スリーカウントの処理
	ThreeCountProcess();
}

void GameStart::Render()
{
	if (m_endJudgement) return;

	if (!m_gameManager->FlagJudgement(GameManager::StartLimitView)) return;

	NumberView();

	if (ThreeCountView()) return;

	m_uiManager->GetStandardShader()->Render(UIManager::GameStartTimeLimit);
}

void GameStart::Finalize()
{
	m_stayTime = 0.0f;
	m_elapsedTime = 0.0f;
	m_numberUpdateFrequency = 0.0f;
	m_numberElapsedTime = 0.0f;
	m_threeCountNumber = 3;
	m_threeCountElapsedTime = 0.0f;
	m_endJudgement = false;
	m_limitJudgement = false;
	m_numberSizeTime = 0.0;
	m_numberRender.reset();
}

void GameStart::NumberView()
{
	if (m_elapsedTime < 1.0f)
	{
		return;
	}

	if (m_numberStayTime > 0.5f)
	{
		return;
	}

	DirectX::SimpleMath::Vector2 windowSize = LibrarySingleton::GetInstance()->GetScreenSize();

	float length = 330.0f;

	float length2 = 130.0f;

	float lengthY = 50.0f;

	(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::GameStartTimeTen].position = { 0.0f, lengthY };
	m_uiManager->GetStandardShader()->Render(UIManager::GameStartTimeTen);

	//		十分単位
	m_numberRender->SetPosition({ windowSize.x / 2.0f - length, windowSize.y / 2.0f + lengthY });
	m_constBuffer.number = { static_cast<float>(m_number / 60 / 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_numberRender->Render(m_constBuffer);

	//		分単位
	m_numberRender->SetPosition({ windowSize.x / 2.0f - length2, windowSize.y / 2.0f + lengthY });
	m_constBuffer.number = { static_cast<float>(m_number / 60 % 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_numberRender->Render(m_constBuffer);

	//		十秒
	m_numberRender->SetPosition({ windowSize.x / 2.0f + length2, windowSize.y / 2.0f + lengthY });
	m_constBuffer.number = { static_cast<float>(m_number % 60 / 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_numberRender->Render(m_constBuffer);

	//		秒
	m_numberRender->SetPosition({ windowSize.x / 2.0f + length, windowSize.y / 2.0f + lengthY });
	m_constBuffer.number = { static_cast<float>(m_number % 60 % 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_numberRender->Render(m_constBuffer);
}

bool GameStart::ThreeCountView()
{
	//		時間待機時間が0.5以下の場合処理をしない
	if (m_numberStayTime < 0.5f) return false;

	//		ウィンドウサイズを受け取る
	DirectX::SimpleMath::Vector2 windowSize = LibrarySingleton::GetInstance()->GetScreenSize();

	//		座標を中心にする
	m_numberRender->SetPosition({ windowSize.x / 2.0f, windowSize.y / 2.0f });

	//		サイズを変更する
	m_numberRender->SetSize({ 1.5f, 1.5f });
	
	//		数字の変更
	m_constBuffer.number = { static_cast<float>(m_threeCountNumber), 0.0f, 0.0f, 0.0f };

	//		描画
	m_numberRender->Render(m_constBuffer);

	return true;
}

bool GameStart::TimeLimitMove()
{
	//		経過時間が1秒以上の場合処理をしない
	if (m_elapsedTime >= 1.0f) return false;

	//		経過時間
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	float move = 0.0f;

	//		一秒以上にならないようにする
	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	//		イージング
	if (m_elapsedTime == 1.0f)
	{
		move = 1.0f;
	}
	else
	{
		move = 1.0f - pow(2.0f, -10.0f * m_elapsedTime);
	}

	//		ラープを使い移動させる
	(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::GameStartTimeLimit].position =
	{ 0.0f, Library::Lerp(0.0f, -200.0f, move) };

	return true;
}

bool GameStart::TimeLimitNumberRandom()
{
	if (m_limitJudgement) return false;

	//		経過時間
	m_numberElapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 1.5f;

	//		更新時間が経過時間より大きい場合
	if (m_numberElapsedTime > m_numberUpdateFrequency)
	{
		//		二乗分の値を足す
		m_numberUpdateFrequency += (m_numberElapsedTime * m_numberElapsedTime);

		//		乱数で番号を出す
		m_number = static_cast<int>(LibrarySingleton::GetInstance()->Random(0.0f, 9999.0f));

		//		経過時間をリセットする
		m_numberElapsedTime = 0.0f;

		//		更新時間が一定量を超えた場合
		if (m_numberUpdateFrequency >= 0.7f)
		{
			//		本命の時間にする
			m_number = static_cast<int>(m_limitTime);

			//		これ以上処理をしない
			m_limitJudgement = true;
		}
	}

	return true;
}

void GameStart::ThreeCountProcess()
{
	m_threeCountElapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_threeCountElapsedTime > 1.0f)
	{
		m_threeCountNumber -= 1;

		m_threeCountElapsedTime = 0.0f;

		if (m_threeCountNumber == 0)
		{
			m_gameManager->TrueFlag(GameManager::GameStart);

			m_endJudgement = true;
		}
	}
}

bool GameStart::NumberSizeTime()
{
	if (m_numberSizeTime >= 1.0f) return false;

	m_numberSizeTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	m_numberSizeTime = Library::Clamp(m_numberSizeTime, 0.0f, 1.0f);

	float move = 0.0f;

	if (m_numberSizeTime == 1)
	{
		move = 1.0f;
	}
	else
	{
		move = 1.0f - pow(2.0f, -10.0f * m_numberSizeTime);
	}

	float size = Library::Lerp(1.0f, 1.05f, move);

	m_numberRender->SetSize({ size, size });

	return true;
}
