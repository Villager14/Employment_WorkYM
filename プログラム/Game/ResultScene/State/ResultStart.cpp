/*
* @file		ResultStart.cpp
* @brief	���U���g�J�n����
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
	//		�^�C�g����BGM�̍Đ�
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		���j���[���g���Ȃ��悤�ɂ���
	m_resultManager->SetMenuUseJugement(false);

	m_time = 0.0f;
}

void ResultStart::Update()
{
	//		�o�ߎ���
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		���ʂ��������グ��
	MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

	if (m_time >= 1.0f)
	{
		//		��Ԃ�؂�ւ���(�����ړ����)
		m_resultManager->ChangeState(ResultManager::State::NumberMove);
	}
}

void ResultStart::Render()
{
	//		UI�w�i�̕`��
	//m_resultManager->UIViewProcess(0);

	//		�t�F�[�h
	m_resultManager->GetInformation()->FadeViewProcess(m_time);
}

void ResultStart::Finalize()
{
	//		���j���[���g����悤�ɂ���
	m_resultManager->SetMenuUseJugement(true);
}
