/*
* @file		ChangeSceneState.cpp
* @brief	�V�[���؂�ւ����������
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "ChangeSceneState.h"

ChangeSceneState::ChangeSceneState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(1.0f)
{
}

ChangeSceneState::~ChangeSceneState()
{
}

void ChangeSceneState::Initialize()
{
	m_time = 1.0f;

	//		���j���[���g����悤�ɂ���
	m_titleSelectManager->GetInformation()->SetMenuUseJudgement(false);

	//		���ʉ�
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);
}

void ChangeSceneState::Update()
{
	m_time -= LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�Q�[���I�����̉��ʂ̃{�����[������
	MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

	if (m_time <= 0.0f)
	{
		//		�v���C�V�[���ɐ؂�ւ���
		m_titleSelectManager->GetInformation()->SetChangeSceneJudgement(true);
	}
}

void ChangeSceneState::Render()
{
	//		�t�F�[�h�̕`��
	m_titleSelectManager->GetInformation()->FadeViewProcess(m_time);
}

void ChangeSceneState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);
	m_time = 0.0f;
}
