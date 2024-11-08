/*
* @file		MenuStart.cpp
* @brief	���j���[�X�^�[�g���̏���
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuStart.h"

MenuStart::MenuStart(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
	m_scale(0.0f),
	m_move(0.0f),
	m_transitionTitleTime(0.0f),
	m_transitionRoughTime(0.0f),
	m_transitionSettingUITime(0.0f),
	m_startJudgement(true)
{
}

MenuStart::~MenuStart()
{
}

void MenuStart::Initialize()
{
	m_scale = 0.0f;
	m_move = 0.0f;
	m_transitionTitleTime = 0.0f;
	m_transitionRoughTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;
}

void MenuStart::Update()
{
	m_menuManager->GetInformation()->SetMenuTransrationJudgement(true);

	if (m_scale < 1.0f)
	{
		m_scale += LibrarySingleton::GetInstance()->GetElpsedTime() * m_menuManager->GetInformation()->MENU_SPEED;

		m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

		float transrationTime = m_menuManager->EasingBackUI(m_scale);

		//		�o�[�P�̃X�P�[���g��
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar1].scale =
		{ transrationTime, 1.0f };

		//		�o�[�Q�̃X�P�[���g��
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar2].scale =
		{ transrationTime, 1.0f };
	}
	else
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime() * m_menuManager->GetInformation()->MENU_SPEED;

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float transrationTime = m_menuManager->EasingBackUI(m_move);

		//		�o�[�P�̈ړ�
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar1].position =
		{ 0.0f, Library::Lerp(13.0f, 300.0f, transrationTime) };

		//		�o�[�Q�̈ړ�
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar2].position =
		{ 0.0f, Library::Lerp(-13.0f, -300.0f, transrationTime) };

		//		�w�i�̃X�P�[���k��
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::BackGround].scale =
		{ 1.0f, transrationTime };

	}

	if (m_move < 1.0f) return;

	//		���j���[�̑J�ڏ���
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, false, true)) return;

	if (!m_startJudgement)
	{
		m_menuManager->ChangState(MenuInformation::MenuType::Audio);
	}

}

void MenuStart::Render()
{
	//		���j���[�̔w�i�̕`��
	m_menuManager->MenuBackRneder();


	//		Audio�̃^�C�g���`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::AudioTitle, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionTitleTime)));

	//		Audio�̕`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::AudioSelect, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionRoughTime)));

	//		Opetion�̕`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::OptionSelect, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionRoughTime)));

	//		GamePlay�̕`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::GamePlaySelect, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionRoughTime)));

	//		�X���C�_�[�̕`��
	SliderView(m_menuManager->EasingIcon(m_transitionSettingUITime));
}

void MenuStart::Finalize()
{
}

void MenuStart::SliderView(float transitionTime)
{
	//		�}�X�^�[�{�����[���̕`��
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, -100.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MastarVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::MastarVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MasterKnob, transitionTime);

	//		BGM�{�����[���̕`��
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, 50.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::BGMVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMKnob, transitionTime);

	//		���ʉ��̕`��
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, 200.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::SoundEffect, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectKnob, transitionTime);
}
