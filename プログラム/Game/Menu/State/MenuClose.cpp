/*
* @file		MenuClose.cpp
* @brief	���j���[����鎞�̏���
* @author	Morita
* @date		2024/07/11
*/

#include "pch.h"

#include "MenuClose.h"

MenuClose::MenuClose(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
	m_scale(0.0f),
	m_move(0.0f),
	m_mainClose(0.0f)
{
}

MenuClose::~MenuClose()
{
}

void MenuClose::Initialize()
{
	m_move = 0.0f;
	m_scale = 0.0f;
	m_mainClose = 1.0f;
	m_menuManager->GetInformation()->SetMenuTransrationJudgement(false);
}

void MenuClose::Update()
{

	if (m_move < 1.0f)
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime() * m_menuManager->GetInformation()->MENU_SPEED;

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float transrationTime = m_menuManager->EasingBackUI(m_move);

		//		�o�[�P�̈ړ�
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar1].position =
		{ 0.0f, Library::Lerp(300.0f, 13.0f, transrationTime) };

		//		�o�[�Q�̈ړ�
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar2].position =
		{ 0.0f, Library::Lerp(-300.0f, -13.0f, transrationTime) };

		//		�w�i�̃X�P�[���k��
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::BackGround].scale =
		{ 1.0f, 1 - transrationTime };
	}
	else
	{
			m_scale += LibrarySingleton::GetInstance()->GetElpsedTime() * m_menuManager->GetInformation()->MENU_SPEED;

			m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

			float transrationTime = m_menuManager->EasingBackUI(m_scale);

			//		�o�[�P�̃X�P�[���k��
			(*m_menuManager->GetInformation()->GetStandardShader()
				->GetUIInformation())[MenuInformation::UIType::Bar1].scale =
			{ 1.0f - transrationTime, 1.0f };

			//		�o�[�Q�̃X�P�[���k��
			(*m_menuManager->GetInformation()->GetStandardShader()
				->GetUIInformation())[MenuInformation::UIType::Bar2].scale =
			{ 1.0f - transrationTime, 1.0f };
	}

	if (m_scale >= 1.0f)
	{
		//m_menuManager->ChangState(MenuInformation::MenuType::Start);

		Finalize();
	}
}

void MenuClose::Render()
{
	//		���j���[�̔w�i�̕`��
	m_menuManager->MenuBackRneder();
}

void MenuClose::Finalize()
{
	//		���j���[���I������
	m_menuManager->GetInformation()->SetMenuJudgement(false);
	m_menuManager->SetFirstAudioMenuJudgement(true);
}
