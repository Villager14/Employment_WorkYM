/*
* @file		OptionSetting.cpp
* @brief	�I�v�V�����̐ݒ�
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "OptionSetting.h"

OptionSetting::OptionSetting(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
	m_transitionTitleTime(0.0f),
	m_transitionSettingUITime(0.0f),
	m_startJudgement(true),
	m_endJudgement(false),
	m_menuCloseJudgement(false),
	m_transitionRoughTime(1.0f)
{
}

OptionSetting::~OptionSetting()
{
}

void OptionSetting::Initialize()
{
}

void OptionSetting::Update()
{
	//		���j���[�̑J�ڏ���
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement)) return;

	//		ESC�Ń��j���[���Ƃ��鏈��
	if (m_menuManager->GetCommonProcess()->MenuEscCloseProcess())
	{
		//		���j���[������Ԃɂ���
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		��܂��ȃ��j���[�{�^���̏���
	if (m_menuManager->GetCommonProcess()->ButtonCollider(MenuInformation::MenuType::Option))
	{
		m_endJudgement = true;
	}

	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::FOVKnob);
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::MouseKnob);

	float fov = ((*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::FOVKnob].position.x - (-96.0f)) / (496.0f - (-96.0f));

	//		�}�X�^�[�{�����[���̃X���C�_�[�̍X�V
	(*m_menuManager->GetInformation()->GetSlider()->GetInformation())[Slider::UIType::FOV].slideVal = fov;
		
	m_menuManager->GetInformation()->SetViewAngle(Library::Lerp(70.0f, 120.0f, fov));


	float mouse = ((*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::MouseKnob].position.x - (-96.0f)) / (496.0f - (-96.0f));

	//		�}�X�^�[�{�����[���̃X���C�_�[�̍X�V
	(*m_menuManager->GetInformation()->GetSlider()->GetInformation())[Slider::UIType::Mouse].slideVal = mouse;

	m_menuManager->GetInformation()->SetCameraSpeed(Library::Lerp(0.1f, 10.0f, mouse));

}

void OptionSetting::Render()
{
	m_menuManager->MenuBackRneder();

	//		Option�̃^�C�g���`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::OptionTitle, m_menuManager->EasingIcon(m_transitionTitleTime));

	//		���j���[�I�𒆂̕`��
	if (!m_menuCloseJudgement) m_menuManager->MenuSelectView();

	//		��܂��ȃ��j���[�̕`��
	m_menuManager->RoughMenuViwe(m_menuManager->EasingIcon(m_transitionRoughTime));

	float transitionTime = m_menuManager->EasingIcon(m_transitionSettingUITime);

	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, -100.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::FOV, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::FOV, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::FOVKnob, transitionTime);

	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, 50.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::Mouse, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::Mouse, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MouseKnob, transitionTime);

	//		�}�E�X�|�C���^�̕`��
	m_menuManager->GetCommonProcess()->MousePointa();
}

void OptionSetting::Finalize()
{
	m_transitionTitleTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;
	m_endJudgement = false;
	m_menuCloseJudgement = false;
	m_transitionRoughTime = 1.0f;
}
