/*
* @file		ResultNumberMove.cpp
* @brief	���U���g�����ړ�����
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
		//		��Ԃ�؂�ւ���(�]�����)
		m_resultManager->ChangeState(ResultManager::State::Evaluation);
	}

	//	�A�j���[�V�����̃X�L�b�v
	m_resultManager->AnimationSkip();
}

void ResultNumberMove::Render()
{
	//		�����̕`��
	m_resultManager->GetInformation()->GetRiseNumber()->Render(m_time);
}

void ResultNumberMove::Finalize()
{
}
