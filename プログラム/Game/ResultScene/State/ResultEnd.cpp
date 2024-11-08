/*
* @file		ResultEnd.cpp
* @brief	リザルト終了処理
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "ResultEnd.h"

ResultEnd::ResultEnd(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(1.0f)
{
}

ResultEnd::~ResultEnd()
{
}

void ResultEnd::Initialize()
{
	//		メニューを使えないようにする
	m_resultManager->SetMenuUseJugement(false);

	m_time = 1.0f;
}

void ResultEnd::Update()
{
	m_time -= LibrarySingleton::GetInstance()->GetElpsedTime();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		音量を少しずつ上げる
	MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

	if (m_time <= 0.0f)
	{
		//		タイトルシーンへ
		m_resultManager->GetInformation()->SetChangeSceneJudgement(true);
	}
}

void ResultEnd::Render()
{
	//		評価
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::EvaluationUI);

	//		遷移誘導画像
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::Button);

	//		数字の描画
	m_resultManager->GetInformation()->GetRiseNumber()->Render(4.0f);

	//		フェード処理
	m_resultManager->GetInformation()->FadeViewProcess(m_time);
}

void ResultEnd::Finalize()
{
}
