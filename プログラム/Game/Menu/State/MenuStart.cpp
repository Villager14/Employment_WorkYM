/*
* @file		MenuStart.cpp
* @brief	ƒƒjƒ…[ƒXƒ^[ƒgŽž‚Ìˆ—
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

		//		ƒo[‚P‚ÌƒXƒP[ƒ‹Šg‘å
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar1].scale =
		{ transrationTime, 1.0f };

		//		ƒo[‚Q‚ÌƒXƒP[ƒ‹Šg‘å
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar2].scale =
		{ transrationTime, 1.0f };
	}
	else
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime() * m_menuManager->GetInformation()->MENU_SPEED;

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float transrationTime = m_menuManager->EasingBackUI(m_move);

		//		ƒo[‚P‚ÌˆÚ“®
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar1].position =
		{ 0.0f, Library::Lerp(13.0f, 300.0f, transrationTime) };

		//		ƒo[‚Q‚ÌˆÚ“®
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar2].position =
		{ 0.0f, Library::Lerp(-13.0f, -300.0f, transrationTime) };

		//		”wŒi‚ÌƒXƒP[ƒ‹k¬
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::BackGround].scale =
		{ 1.0f, transrationTime };

	}

	if (m_move < 1.0f) return;

	//		ƒƒjƒ…[‚Ì‘JˆÚˆ—
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, false, true)) return;

	if (!m_startJudgement)
	{
		m_menuManager->ChangState(MenuInformation::MenuType::Audio);
	}

}

void MenuStart::Render()
{
	//		ƒƒjƒ…[‚Ì”wŒi‚Ì•`‰æ
	m_menuManager->MenuBackRneder();


	//		Audio‚Ìƒ^ƒCƒgƒ‹•`‰æ
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::AudioTitle, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionTitleTime)));

	//		Audio‚Ì•`‰æ
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::AudioSelect, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionRoughTime)));

	//		Opetion‚Ì•`‰æ
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::OptionSelect, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionRoughTime)));

	//		GamePlay‚Ì•`‰æ
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::GamePlaySelect, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionRoughTime)));

	//		ƒXƒ‰ƒCƒ_[‚Ì•`‰æ
	SliderView(m_menuManager->EasingIcon(m_transitionSettingUITime));
}

void MenuStart::Finalize()
{
}

void MenuStart::SliderView(float transitionTime)
{
	//		ƒ}ƒXƒ^[ƒ{ƒŠƒ…[ƒ€‚Ì•`‰æ
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, -100.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MastarVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::MastarVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MasterKnob, transitionTime);

	//		BGMƒ{ƒŠƒ…[ƒ€‚Ì•`‰æ
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, 50.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::BGMVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMKnob, transitionTime);

	//		Œø‰Ê‰¹‚Ì•`‰æ
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, 200.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::SoundEffect, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectKnob, transitionTime);
}
