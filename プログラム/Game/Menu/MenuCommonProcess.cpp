/*
* @file		MenuCommonProcess.cpp
* @brief	���j���[�̋��ʏ���
* @author	Morita
* @date		2024/08/05
*/

#include "pch.h"

#include "MenuCommonProcess.h"

MenuCommonProcess::MenuCommonProcess(MenuInformation* menuInformation)
	:
	m_information(menuInformation)
{
}

MenuCommonProcess::~MenuCommonProcess()
{
}

bool MenuCommonProcess::MenuEscCloseProcess()
{
	//		ESC�L�[���������ꍇ
	if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()
		->IsKeyPressed(DirectX::Keyboard::Tab))
	{
		return true;
	}

	return false;
}

bool MenuCommonProcess::BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max)
{
	DirectX::SimpleMath::Vector2 mousePosition;

	mousePosition.x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	mousePosition.y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	//		�͈͓��Ƀ}�E�X�����邩�ǂ���
	if (min.x <= mousePosition.x && max.x >= mousePosition.x &&
		min.y <= mousePosition.y && max.y >= mousePosition.y)
	{
		//		�͈͓�
		return true;
	}

	//		�͈͊O
	return false;
}

bool MenuCommonProcess::ButtonCollider(MenuInformation::MenuType type)
{
	MenuInformation::MenuType hitType = MenuInformation::MenuType::Empty;

	//		�͈͓��ɂ��邩�ǂ����̃t���O
	bool hitJudgement = false;

	//		Audio�̑�܂��{�^�����ɂ��邩�H
	if (BoxCollider(m_information->AUDIO_TITLE_POSITION_MIN, m_information->AUDIO_TITLE_POSITION_MAX))
	{
		//		�͈͓��ɂ���UI��Audio�ɂ���
		m_information->SetRangeUI(AboveUI::AudioSelect);

		//		�͈͓��ɂ���
		hitJudgement = true;

		//		�͈͂ɂ�����̂����݂̏�ԂłȂ���Ώ���������
		if (MenuInformation::MenuType::Audio != type)
			hitType = MenuInformation::MenuType::Audio;
	}

	//		Option�̑�܂��ȃ{�^�����ɂ��邩�H
	if (BoxCollider(m_information->OPTION_TITLE_POSITION_MIN, m_information->OPTION_TITLE_POSITION_MAX))
	{
		//		�͈͓��ɂ���UI��Option�ɂ���
		m_information->SetRangeUI(AboveUI::OptionSelect);

		//		�͈͓��ɂ���
		hitJudgement = true;

		//		�͈͂ɂ�����̂����݂̏�ԂłȂ���Ώ���������
		if (MenuInformation::MenuType::Option != type)
			hitType = MenuInformation::MenuType::Option;
	}

	//		Back�̑�܂��ȃ{�^���̒��ɂ��邩�H
	if (BoxCollider(m_information->GAMEPLAY_TITLE_POSITION_MIN, m_information->GAMEPLAY_TITLE_POSITION_MAX))
	{
		//		�͈͓��ɂ���UI��GamePlay�ɂ���
		m_information->SetRangeUI(AboveUI::GamePlaySelect);

		//		�͈͓��ɂ���
		hitJudgement = true;

		//		�͈͂ɂ�����̂����݂̏�ԂłȂ���Ώ���������
		if (MenuInformation::MenuType::GamePlay != type)
			hitType = MenuInformation::MenuType::GamePlay;
	}

	//		�͈͓��ɂ��Ȃ��ꍇ
	if (!hitJudgement)
	{
		//		�I�����Ă��Ȃ���Ԃɂ���
		m_information->SetRangeUI(AboveUI::Empty);

		//		���Ԃ̃��Z�b�g
		m_information->GetMenuSelect()->TimeReset();
	}

	//		�������Ă��Ȃ��ꍇ����ȏ㏈�������Ȃ�
	if (hitType == MenuInformation::MenuType::Empty) return false;

	//		�͈͓��ŃN���b�N�����ꍇ
	if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
		== DirectX::Mouse::ButtonStateTracker().PRESSED)
	{
		//		�N���b�N������Ԃ�������
		m_information->SetSelectUI(hitType);

		MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

		return true;
	}

	return false;
}

void MenuCommonProcess::SlideProcess(AboveUI::UIType type)
{
	//		���݂̍��W
	DirectX::SimpleMath::Vector2 nowPosition = (*m_information->GetAboveUI()->GetInformation())[type].position;

	//		���S���W
	nowPosition += {  LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f,
		LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f };

	DirectX::SimpleMath::Vector2 max = nowPosition + m_information->KNOB_LENGTH;
	DirectX::SimpleMath::Vector2 min = nowPosition - m_information->KNOB_LENGTH;

	//		�l�p�̓����蔻��
	if (BoxCollider(min, max))
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			m_information->SetSliderSelectUI(type);
		}
	}

	if (m_information->GetSliderSelectUI() == type)
	{
		(*m_information->GetAboveUI()->GetInformation())[type].position.x = static_cast<float>
			(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x) - 640.0f;

		(*m_information->GetAboveUI()->GetInformation())[type].position.x = Library::Clamp
		((*m_information->GetAboveUI()->GetInformation())[type].position.x,
			-81.0f, 480.0f);


		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().RELEASED)
		{
			//		���ʉ��̏ꍇ�̂ݗ������Ƃ����ʉ���炷
			if (m_information->GetSliderSelectUI() == AboveUI::UIType::SoundEffectKnob)
				MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

			m_information->SetSliderSelectUI(AboveUI::UIType::Empty);

		}
	}

}

void MenuCommonProcess::MousePointa()
{
	//		�}�E�X�̍��W
	DirectX::SimpleMath::Vector2 mousePosition;

	//		�}�E�X�̌��ݍ��W���󂯎��
	mousePosition.x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x) - LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f;
	mousePosition.y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y) - LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f;

	//		�}�E�X�|�C���^��UI�̍��W��ݒ肷��
	(*m_information->GetStandardShader()->GetUIInformation())[MenuInformation::UIType::MousePointa].position = mousePosition;

	//		�}�E�X�|�C���^�̕`��
	m_information->GetStandardShader()->Render(MenuInformation::UIType::MousePointa);
}
