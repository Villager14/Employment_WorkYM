/*
* @file		ResultStart.cpp
* @brief	リザルト開始処理
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultStart.h"

ResultStart::ResultStart(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultStart::~ResultStart()
{
}

void ResultStart::Initialize()
{
	//		タイトルのBGMの再生
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		メニューを使えないようにする
	m_resultManager->SetMenuUseJugement(false);

	m_time = 0.0f;
}

void ResultStart::Update()
{
	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		音量を少しずつ上げる
	MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

	if (m_time >= 1.0f)
	{
		//		状態を切り替える(数字移動状態)
		m_resultManager->ChangeState(ResultManager::State::NumberMove);
	}
}

void ResultStart::Render()
{
	//		UI背景の描画
	//m_resultManager->UIViewProcess(0);

	//		フェード
	m_resultManager->GetInformation()->FadeViewProcess(m_time);
}

void ResultStart::Finalize()
{
	//		メニューを使えるようにする
	m_resultManager->SetMenuUseJugement(true);
}
