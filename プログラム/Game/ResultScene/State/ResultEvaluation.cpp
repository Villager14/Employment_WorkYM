/*
* @file		ResultEvaluation.cpp
* @brief	リザルト評価処理
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "ResultEvaluation.h"

ResultEvaluation::ResultEvaluation(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultEvaluation::~ResultEvaluation()
{
}

void ResultEvaluation::Initialize()
{
	m_time = 0.0f;

	(*m_resultManager->GetInformation()->GetStandardShader()->GetUIInformation())[ResultInformation::EvaluationUI].scale = { 1, 0.0f };
}

void ResultEvaluation::Update()
{
	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	float size = 0.0f;

	size = Easing(m_time);

	//		評価
	(*m_resultManager->GetInformation()->GetStandardShader()->GetUIInformation())
		[ResultInformation::EvaluationUI].scale = { 1.0f, size };


	if (m_time >= 1.0f)
	{
		//		状態を切り替える(待機状態)
		m_resultManager->ChangeState(ResultManager::State::Stay);
	}

	//	アニメーションのスキップ
	m_resultManager->AnimationSkip();
}

void ResultEvaluation::Render()
{
	//		評価
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::EvaluationUI);

	//		数字の描画
	m_resultManager->GetInformation()->GetRiseNumber()->Render(4.0f);
}

void ResultEvaluation::Finalize()
{
}

float ResultEvaluation::Easing(float time)
{
	if (time < 0.5f)
	{
		return 4.0f * time * time * time;
	}
	else
	{
		return 1.0f - pow(-2.0f * time + 2.0f, 3.0f) / 2.0f;
	}
}
