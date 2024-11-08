/*
* @file		FadeIn.h
* @brief	フェードの処理
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "FadeIn.h"

FadeIn::FadeIn()
	:
	m_time(0.0f),
	m_fadeinResetJudgement(true),
	m_fadeoutResetJudgement(false),
	m_stayTime(0.0f),
	m_firstJudgement(true)
{
	//		フェード描画の生成
	m_fadeRender = std::make_unique<UIRenderManager>();

}

FadeIn::~FadeIn()
{
}

void FadeIn::Initialize()
{
	m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		L"Resources/Shader/UI/Fade/FadeShaderVS.cso",
		L"Resources/Shader/UI/Fade/FadeShaderGS.cso",
		L"Resources/Shader/UI/Fade/FadeShaderPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	buffer.rotationMatrix = m_fadeRender->GetRotationMatrix();

	m_time = 0.0f;

	m_stayTime = 0.0f;
}

void FadeIn::Update(GameManager* gameManager)
{
	//		終了の場合
	if (gameManager->FlagJudgement(GameManager::EndJudgement))
	{
		m_stayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		if (m_stayTime <= 1.0f) return;

		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 1.0f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		//		プレイシーン終了時の音量調整
		MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

		if (m_time <= 0.0f)
		{
			//		次のシーンに切り替える
			gameManager->TrueFlag(GameManager::NextScene);
		}

		return;
	}

	//		復活状態＆フェードアウトをしない状態の場合
	if (gameManager->FlagJudgement(GameManager::RevivalJudgement)
		&& !m_fadeoutResetJudgement)
	{
		m_fadeoutResetJudgement = true;

		m_time = 1.0f;
	}

	//		フェードインの処理
	if (m_fadeinResetJudgement)
	{
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_firstJudgement)
		{
			//		プレイシーン開始時の音量調整
			MusicLibrary::GetInstance()->SceneLerpVolume(m_time);
		}

		if (m_time > 1.0f)
		{
			m_fadeinResetJudgement = false;
		}
	}

	//		フェードアウトの処理
	if (m_fadeoutResetJudgement)
	{
		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 4.0f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_time <= 0.0f)
		{
			m_fadeoutResetJudgement = false;

			//		復活状態を終了
			gameManager->FalseFlag(GameManager::RevivalJudgement);
			gameManager->FalseFlag(GameManager::DeathJudgement);
			m_fadeinResetJudgement = true;
		}
	}
}

void FadeIn::Render()
{
	buffer.time = { Library::Clamp(m_time, 0.0f, 1.0f) , 0.0f, 0.0f, 0.0f };

	m_fadeRender->Render(buffer);
}

void FadeIn::Finalize()
{
	m_fadeRender->Finalize();
}
