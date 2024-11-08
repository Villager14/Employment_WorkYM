/*
* @file		GameClearManager.cpp
* @brief	ゲームクリアマネージャー
* @author	Morita
* @date		2024/05/23
*/

#include "pch.h"

#include "GameClearManager.h"


GameClearManager::GameClearManager(GameManager* gameManager, UIManager* uiManager)
	:
	m_gameManager(gameManager),
	m_elapsedTime(0.0f),
	m_scale(0.0f),
	m_move(0.0f),
	m_uiManager(uiManager)
{
}

GameClearManager::~GameClearManager()
{
}

void GameClearManager::Initialize()
{
	//		メッセージ描画シェーダーの生成
	m_messageShader = std::make_unique<UIRenderManager>();

	//		メッセージの作成
	m_messageShader->Create(L"Resources/Texture/UI/GameClear/Messege.png",
		L"Resources/Shader/UI/CenterShader/CenterShaderVS.cso",
		L"Resources/Shader/UI/CenterShader/CenterShaderGS.cso",
		L"Resources/Shader/UI/CenterShader/CenterShaderPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f }
	);

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	buffer.rotationMatrix = m_messageShader->GetRotationMatrix();

	m_elapsedTime = 0.0f;
	m_scale = 0.0f;
	m_move = 0.0f;

	(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBarUnder].scale = { 0.0f, 1.0f };
	(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBarUp].scale = { 0.0f, 1.0f };
	(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBarUnder].position = { 0.0f, 13.0f };
	(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBarUp].position = { 0.0f, 13.0f };
	(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBackGround].scale = { 1.0f, 0.0f };
	buffer.time = { 0.0f, 0.0f, 0.0f, 0.0f };
}

void GameClearManager::Update()
{
	//		ゲームクリア状態ではないなら処理をしない
	if (!m_gameManager->FlagJudgement(GameManager::GoalJudgement)) return;

	if (m_scale < 1.0f)
	{

		m_scale += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

		float move = 0.0f;

		if (m_scale == 1.0f)
		{
			move = 1.0f;
		}
		else
		{
			move = 1.0f - pow(2.0f, -10.0f * m_scale);
		}

		(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBarUnder].scale = { move, 1.0f };
		(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBarUp].scale = { move, 1.0f };
	}
	else
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float move = 0.0f;

		if (m_move == 1.0f)
		{
			move = 1.0f;
		}
		else
		{
			move = 1.0f - pow(2.0f, -10.0f * m_move);
		}

		(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBarUnder].position = { 0.0f, Library::Lerp(13.0f, 300.0f, move) };
		(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBarUp].position = { 0.0f, Library::Lerp(-13.0f, -300.0f, move) };

		(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::UIType::GameClearBackGround].scale = { 1.0f, move };
		buffer.time = { move, 0.0f, 0.0f, 0.0f };
	}

}

void GameClearManager::Render()
{
	//		ゲームクリア状態ではないなら処理をしない
	if (!m_gameManager->FlagJudgement(GameManager::GoalJudgement)) return;

	m_uiManager->GetStandardShader()->Render(UIManager::UIType::GameClearBackGround);

	m_messageShader->Render(buffer);

	m_uiManager->GetStandardShader()->Render(UIManager::UIType::GameClearBarUnder);
	m_uiManager->GetStandardShader()->Render(UIManager::UIType::GameClearBarUp);
}

void GameClearManager::Finalize()
{
	m_elapsedTime = 0.0f;
	m_scale = 0.0f;
	m_move = 0.0f;
	m_messageShader.reset();
}
