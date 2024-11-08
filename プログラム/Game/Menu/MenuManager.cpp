/*
* @file		MenuManager.cpp
* @brief	���j���[�̃}�l�[�W���[
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuManager.h"

#include <Windows.h>

#include "Effect/UI/Menu/AboveUI/AboveUI.h"
#include "Effect/UI/Menu/Slider/Slider.h"
#include "Effect/UI/Menu/MenuSelect/MenuSelect.h"
#include "Effect/UI/Menu/FrameWalkUI/FrameWalkUI.h"


MenuManager::MenuManager(SceneManager* sceneManager)
	:
	m_state(),
	m_type{},
	m_firstAudioMenuJudgement(true),
	m_sceneManager(sceneManager)
{
	//		��Ԃ̐���
	m_menuStateInformation.insert({ MenuInformation::Start, std::make_unique<MenuStart>(this) });
	m_menuStateInformation.insert({ MenuInformation::Audio, std::make_unique<AudioSetting>(this) });
	m_menuStateInformation.insert({ MenuInformation::Option, std::make_unique<OptionSetting>(this) });
	m_menuStateInformation.insert({ MenuInformation::GamePlay, std::make_unique<EndSetting>(this) });
	m_menuStateInformation.insert({ MenuInformation::Close, std::make_unique<MenuClose>(this) });

	//		UI���쐬����
	CreateUI();

	m_commonProcess = std::make_unique<MenuCommonProcess>(m_information.get());
}

MenuManager::~MenuManager()
{
}

void MenuManager::Initialize()
{

	m_type = MenuInformation::Start;

	//		�����̏��
	m_state = m_menuStateInformation[m_type].get();

	//		����������
	m_state->Initialize();

		//		�}�E�X�𑊑Έʒu�ɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);
}

void MenuManager::Update()
{
	//		���j���[���g�p���邱�Ƃ��ł��邩�ǂ���
	if (!m_information->GetMenuUseJudgement()) return;

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	if (keyboard.IsKeyPressed(DirectX::Keyboard::Tab))
	{
		ShowCursor(FALSE);

		m_information->SetMenuJudgement(true);
	}

	//		���j���[���g�p���邩�ǂ���
	if (!m_information->GetMenuJudgement()) return;

	//		�������������s�����ǂ���
	if (m_information->GetInitializeJudgement())
	{
		Initialize();

		m_information->SetInitializeJudgement(false);
	}

	//		�X�V����
	m_state->Update();

	//		���j���[���[�h���I�������Ƃ�
	if (!m_information->GetMenuJudgement())
	{
		//		�}�E�X���΃��[�h
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

		Finalize();
	}
}

void MenuManager::Render()
{
	//		���j���[���g�p���Ă��邩�ǂ���
	if (!m_information->GetMenuJudgement()) return;

	//		�`�揈��
	m_state->Render();

	//		�f�o�b�N�t�H���g
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionX",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x), 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionY",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y), 0, 30);
	LibrarySingleton::GetInstance()->DebugFont(L"HitJudgement",
		m_commonProcess->BoxCollider(m_information->GAMEPLAY_TITLE_POSITION_MIN, m_information->GAMEPLAY_TITLE_POSITION_MAX), 0, 60);
}

void MenuManager::Finalize()
{
	m_information->SetInitializeJudgement(true);
}

void MenuManager::MenuBackRneder()
{
	//		�w�i�̕`��
	m_information->GetStandardShader()->Render(MenuInformation::UIType::BackGround);

	//		�o�[�P�̕`��
	m_information->GetStandardShader()->Render(MenuInformation::UIType::Bar1);

	//		�o�[�Q�̕`��
	m_information->GetStandardShader()->Render(MenuInformation::UIType::Bar2);
}

void MenuManager::CreateUI()
{
	//		�X�^���_�[�h�V�F�[�_�[�̐���
	m_standardShader = std::make_unique<StandardShader<MenuInformation::UIType>>();

	//		�X�^���_�[�h�V�F�[�_�[�̏���������
	m_standardShader->Initialize();

	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, 13.0f }, { 0.0f, 1.0f }, MenuInformation::UIType::Bar1);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, -13.0f }, { 0.0f, 1.0f }, MenuInformation::UIType::Bar2);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBack.png",
		{ 0.0f, 0.0f }, { 0.0f, 1.0f }, MenuInformation::UIType::BackGround);
	m_standardShader->CreateUIInformation(L"Resources/Texture/Menu/Title/mousePointa.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f }, MenuInformation::UIType::MousePointa);

	//		�㏸UI�̐���
	m_aboveUI = std::make_unique<AboveUI>();

	//		�㏸UI�̏�����
	m_aboveUI->Initialize();

	//		�X���C�_�[UI�̐���
	m_slider = std::make_unique<Slider>();

	//		�X���C�_�[UI�̏�����
	m_slider->Initialize();

	//		���j���[�I��UI�̐���
	m_menuSelect = std::make_unique<MenuSelect>();

	//		���j���[�I��UI�̏�����
	m_menuSelect->Initialize();

	//		�t���[�����[�N�𐶐�����
	m_frameWalkUI = std::make_unique<FrameWalkUI>();

	//		�t���[�����[�N�𐶐�����
	m_frameWalkUI->Initialize();

	//		���j���[�̏��𐶐�����
	m_information = std::make_unique<MenuInformation>();

	//		���j���[�̏�������������
	m_information->Initialzie(m_standardShader.get(),
		m_aboveUI.get(), m_slider.get(), m_menuSelect.get(), m_frameWalkUI.get());

}

void MenuManager::RoughMenuViwe(float transitionTime)
{
	//		Opetion�̕`��
	m_information->GetAboveUI()->Render(AboveUI::UIType::OptionSelect, transitionTime);

	//		GamePlay�̕`��
	m_information->GetAboveUI()->Render(AboveUI::UIType::GamePlaySelect, transitionTime);

	//		Audio�̃^�C�g���`��
	m_information->GetAboveUI()->Render(AboveUI::UIType::AudioSelect, transitionTime);
}

void MenuManager::MenuSelectView()
{
	//		�I�����Ă��Ȃ��ꍇ�`�揈�������Ȃ�
	if (m_information->GetRangeUI() != AboveUI::UIType::Empty)
		m_information->GetMenuSelect()->Render((*m_information->GetAboveUI()->GetInformation())[m_information->GetRangeUI()].position);
}

void MenuManager::ChangState(MenuInformation::MenuType type)
{
	//		�����^�C�v�̏ꍇ���������Ȃ�
	if (m_type == type) return;

	//		�I������
	m_state->Finalize();

	//		�^�C�v�̍X�V
	m_type = type;

	//		��Ԃ̍X�V
	m_state = m_menuStateInformation[type].get();

	//		����������
	m_state->Initialize();
}

bool MenuManager::Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
							bool* startJudgement, bool endJudgement, bool moveJudgement)
{
	//		�J�n��Ԃ̏ꍇ
	if (*startJudgement)
	{
		//		����1�̍X�V
		*transitionTime1 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

		//		����1����莞�Ԉȏ�ɂȂ����瑼�̎��Ԃ��X�V����
		if (*transitionTime1 > 0.3f)
		{
			//		����2�̍X�V
			*transitionTime2 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

			//		����2����莞�Ԉȏ�3�J�ڃt���O���I���̏ꍇ����3�̍X�V������
			if (*transitionTime2 > 0.3f && moveJudgement)
			{
				//		����3�̍X�V
				*transitionTime3 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;
			}
		}

		//		1�ȏ�ɂȂ�Ȃ��悤�ɂ���
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		//		3�̍X�V������ꍇ
		if (moveJudgement)
		{
			//		3�̍X�V���I�������
			if (*transitionTime3 >= 1.0f)
			{
				//		�J�n��Ԃ��I������
				*startJudgement = false;
			}
		}
		else
		{
			//		2�̍X�V���I�������
			if (*transitionTime2 >= 1.0f)
			{
				//		�J�n��Ԃ��I������
				*startJudgement = false;
			}
		}

		return true;
	}

	//		�I����Ԃ̏ꍇ
	if (endJudgement)
	{
		//		����1�̍X�V
		*transitionTime1 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

		//		����1����莞�Ԉȉ��ɂȂ����瑼�̎��Ԃ��X�V����
		if (*transitionTime1 < 0.7f)
		{
			//		����2�̍X�V
			*transitionTime2 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

			//		����2����莞�Ԉȉ�3�J�ڃt���O���I���̏ꍇ����3�̍X�V������
			if (*transitionTime2 < 0.7f && moveJudgement)
			{
				//		����3�̍X�V
				*transitionTime3 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;
			}
		}

		//		0�ȉ��ɂȂ�Ȃ��悤�ɂ���
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		if (moveJudgement)
		{
			if (*transitionTime3 <= 0.0f)
			{
				//		�V�[����؂�ւ���
				ChangState(MenuInformation::MenuType::Close);
			}
		}
		else
		{
			if (*transitionTime2 <= 0.0f)
			{
				//		�V�[����؂�ւ���
				ChangState(m_information->GetSelectUI());
			}
		}

		return true;
	}

	return false;
}
