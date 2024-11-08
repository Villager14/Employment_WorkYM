/*
* @file		StartSceneState.cpp
* @brief	開始した状態
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "StartSceneState.h"


StartSceneState::StartSceneState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f)
{
}

StartSceneState::~StartSceneState()
{
}

void StartSceneState::Initialize()
{
	m_time = 0.0f;
}

void StartSceneState::Update()
{
	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		ゲーム開始時の音量のボリューム調整
	MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

	//		時間が一以上になったら状態を切り替える
	if (m_time >= 1.0f)
	{
		//		開始状態にする
		m_titleSelectManager->ChangeState(TitleInformation::State::PlayState);
	}
}

void StartSceneState::Render()
{
	//		フェードの描画
	m_titleSelectManager->GetInformation()->FadeViewProcess(m_time);
}

void StartSceneState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);
	m_time = 0.0f;

	//		メニューを使えるようにする
	m_titleSelectManager->GetInformation()->SetMenuUseJudgement(true);
}
