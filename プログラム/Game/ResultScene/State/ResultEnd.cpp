/*
* @file		ResultEnd.cpp
* @brief	���U���g�I������
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
	//		���j���[���g���Ȃ��悤�ɂ���
	m_resultManager->SetMenuUseJugement(false);

	m_time = 1.0f;
}

void ResultEnd::Update()
{
	m_time -= LibrarySingleton::GetInstance()->GetElpsedTime();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		���ʂ��������グ��
	MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

	if (m_time <= 0.0f)
	{
		//		�^�C�g���V�[����
		m_resultManager->GetInformation()->SetChangeSceneJudgement(true);
	}
}

void ResultEnd::Render()
{
	//		�]��
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::EvaluationUI);

	//		�J�ڗU���摜
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::Button);

	//		�����̕`��
	m_resultManager->GetInformation()->GetRiseNumber()->Render(4.0f);

	//		�t�F�[�h����
	m_resultManager->GetInformation()->FadeViewProcess(m_time);
}

void ResultEnd::Finalize()
{
}
