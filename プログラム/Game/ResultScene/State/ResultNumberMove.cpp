/*
* @file		ResultNumberMove.cpp
* @brief	リザルト数字移動処理
* @author	Morita
* @date		2024/05/29
*/

#include "pch.h"

#include "ResultNumberMove.h"

ResultNumberMove::ResultNumberMove(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultNumberMove::~ResultNumberMove()
{
}

void ResultNumberMove::Initialize()
{
	m_time = 0.0f;
}

void ResultNumberMove::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * MOVE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, MAX_TIME);

	if (m_time >= MAX_TIME)
	{
		//		状態を切り替える(評価状態)
		m_resultManager->ChangeState(ResultManager::State::Evaluation);
	}

	//	アニメーションのスキップ
	m_resultManager->AnimationSkip();
}

void ResultNumberMove::Render()
{
	//		数字の描画
	m_resultManager->GetInformation()->GetRiseNumber()->Render(m_time);
}

void ResultNumberMove::Finalize()
{
}
