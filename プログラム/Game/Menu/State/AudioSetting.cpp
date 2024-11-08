/*
* @file		AudioSetting.cpp
* @brief	���̐ݒ�
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "AudioSetting.h"

AudioSetting::AudioSetting(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
	m_transitionTitleTime(1.0f),
	m_transitionSettingUITime(1.0f),
	m_startJudgement(false),
	m_endJudgement(false),
	m_transitionRoughTime(1.0f),
	m_menuCloseJudgement(false)
{
}

AudioSetting::~AudioSetting()
{
}

void AudioSetting::Initialize()
{
	if (m_menuManager->GetFirstAudioMenuJudgement())
	{
		m_transitionTitleTime = 1.0f;
		m_transitionSettingUITime = 1.0f;
		m_startJudgement = false;
		m_endJudgement = false;
		m_menuManager->SetFirstAudioMenuJudgement(false);
	}
}

void AudioSetting::Update()
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
	if (m_menuManager->GetCommonProcess()->ButtonCollider(MenuInformation::MenuType::Audio))
	{
		m_endJudgement = true;
	}

	//		�X���C�_�[�̍X�V����
	SliderUpdate();
}

void AudioSetting::Render()
{
	m_menuManager->MenuBackRneder();

	//		��܂��ȃ��j���[�̕`��
	m_menuManager->RoughMenuViwe(m_menuManager->EasingIcon(m_transitionRoughTime));
	
	//		���j���[�I�𒆂̕`��
	if (!m_menuCloseJudgement) m_menuManager->MenuSelectView();

	//		Audio�̃^�C�g���`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::AudioTitle,
		m_menuManager->EasingIcon(m_transitionTitleTime));

	//		�X���C�_�[�̕`��
	SliderView(m_menuManager->EasingIcon(m_transitionSettingUITime));

	//		�}�E�X�|�C���^�̕`��
	m_menuManager->GetCommonProcess()->MousePointa();
}

void AudioSetting::Finalize()
{
	m_transitionTitleTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;
	m_endJudgement = false;
	m_transitionRoughTime = 1.0f;
	m_menuCloseJudgement = false;
}

void AudioSetting::SliderView(float transitionTime)
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

void AudioSetting::SliderUpdate()
{
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::MasterKnob);
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::BGMKnob);
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::SoundEffectKnob);

	//		�}�X�^�[�{�����[���̃X���C�_�[�̍X�V
	(*m_menuManager->GetInformation()->GetSlider()->GetInformation())[Slider::UIType::MastarVolum].slideVal =
		((*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::MasterKnob].position.x - (-96.0f)) / (496.0f - (-96.0f));

	//		�}�X�^�[�{�����[���̉��ʂ�ݒ肷��
	MusicLibrary::GetInstance()->SetMastaraVolume(((*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())
		[AboveUI::UIType::MasterKnob].position.x - (-81.0f)) / (480.0f - (-81.0f)));

	//		BGM�̃X���C�_�[�̍X�V
	(*m_menuManager->GetInformation()->GetSlider()->GetInformation())[Slider::UIType::BGMVolum].slideVal =
		((*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::BGMKnob].position.x - (-96.0f)) / (496.0f - (-96.0f));

	//		BGM�̉��ʂ�ݒ肷��
	MusicLibrary::GetInstance()->SetBGMVolume(((*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())
		[AboveUI::UIType::BGMKnob].position.x - (-81.0f)) / (480.0f - (-81.0f)));

	//		���ʉ��̃X���C�_�[�̍X�V
	(*m_menuManager->GetInformation()->GetSlider()->GetInformation())[Slider::UIType::SoundEffect].slideVal =
		((*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SoundEffectKnob].position.x - (-96.0f)) / (496.0f - (-96.0f));

	//		���ʉ��̉��ʂ�ݒ肷��
	MusicLibrary::GetInstance()->SetSoundEffectVolume(((*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())
		[AboveUI::UIType::SoundEffectKnob].position.x - (-81.0f)) / (480.0f - (-81.0f)));
}
