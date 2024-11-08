/*
* @file		StartSceneState.cpp
* @brief	�J�n�������
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
	//		�o�ߎ���
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�Q�[���J�n���̉��ʂ̃{�����[������
	MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

	//		���Ԃ���ȏ�ɂȂ������Ԃ�؂�ւ���
	if (m_time >= 1.0f)
	{
		//		�J�n��Ԃɂ���
		m_titleSelectManager->ChangeState(TitleInformation::State::PlayState);
	}
}

void StartSceneState::Render()
{
	//		�t�F�[�h�̕`��
	m_titleSelectManager->GetInformation()->FadeViewProcess(m_time);
}

void StartSceneState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);
	m_time = 0.0f;

	//		���j���[���g����悤�ɂ���
	m_titleSelectManager->GetInformation()->SetMenuUseJudgement(true);
}
