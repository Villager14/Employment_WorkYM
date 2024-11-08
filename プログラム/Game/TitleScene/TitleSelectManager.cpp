/*
* @file		BackGroundMove.cpp
* @brief	�^�C�g���̑I���}�l�[�W���[
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "TitleSelectManager.h"

#include "State/SelectPlayState.h"
#include "State/SelectEndState.h"
#include "State/SelectSettingState.h"
#include "State/ChangeSceneState.h"
#include "State/StartSceneState.h"

TitleSelectManager::TitleSelectManager()
	:
	m_iState(),
	m_state{},
	m_menuInformation(nullptr)
{
	Generation();
}

TitleSelectManager::~TitleSelectManager()
{
}

void TitleSelectManager::Initialize()
{
	//		�}�E�X�̃t�H�[���`�����Z�b�g����
	DirectX::Mouse::Get().ResetScrollWheelValue();

	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	CreateStandardShader();

	//		���̏�����
	m_information->Initilaize(m_backGroundMove.get(), m_standardShader.get(),
		m_fade.get());

	//		�w�i�̏�����
	m_backGroundMove->Initialize();

	//		�X�N���[���G�t�F�N�g�̏�����
	m_screenEffectManager->Initialize();

	//		�v���C���[�̃A�j���[�V����������
	m_playerAnimation->Initialize();

	//----
	//		�^�C�g���̏�Ԃ̍쐻
	//---

	//		�����̏��
	m_state = TitleInformation::State::StartState;
	
	m_iState = (*m_information->GetStateInformation())[m_state].get();

	//		����������
	m_iState->Initialize();
}

void TitleSelectManager::Generation()
{
	//		�^�C�g������ݒ肷��
	m_information = std::make_unique<TitleInformation>();

	//		�w�i�̐���
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		�^�C�g�����ʏ����̐���
	m_commonProcess = std::make_unique<TitleCommonProcess>(m_information.get());

	//		�v���C���[�̃A�j���[�V�����̍쐻
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Title);

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[�̍쐻
	m_screenEffectManager = std::make_unique<ScreenEffectManager>(ScreenEffectManager::ResultScene, nullptr);

	//----
	//		�t�F�[�h�C���A�E�g�̏�����
	//---

	TitleInformation::ConstBuffer buffer = m_information->GetBuffer();

	//		�t�F�[�h�`��̍쐻
	m_fade = std::make_unique<UIRenderManager>();

	//		�t�F�[�h�̍쐬
	m_fade->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		L"Resources/Shader/UI/FadeShader/FadeUIVS.cso",
		L"Resources/Shader/UI/FadeShader/FadeUIGS.cso",
		L"Resources/Shader/UI/FadeShader/FadeUIPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	buffer.rotationMatrix = m_fade->GetRotationMatrix();

	m_information->SetBuffer(buffer);

	//----
	//		�^�C�g���̏�Ԃ̍쐻
	//---

	auto stateInformation = m_information->GetStateInformation();

	//		��Ԃ̏���ݒ肷��
	(*stateInformation).insert({ TitleInformation::State::PlayState, std::make_unique<SelectPlayState>(this) });
	(*stateInformation).insert({ TitleInformation::State::EndState, std::make_unique<SelectEndState>(this) });
	(*stateInformation).insert({ TitleInformation::State::SettingState, std::make_unique<SelectSettingState>(this) });
	(*stateInformation).insert({ TitleInformation::State::StartState, std::make_unique<StartSceneState>(this) });
	(*stateInformation).insert({ TitleInformation::State::ChangState, std::make_unique<ChangeSceneState>(this) });

	//		�`�揇��ݒ肷��
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::Play);
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::Setting);
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::End);
}

void TitleSelectManager::Update()
{
	//		�w�i�̍X�V����
	m_backGroundMove->Update();

	//		���j���[���J���Ă���ꍇ�͏��������Ȃ�
	if (m_menuInformation->GetMenuJudgement()) return;

	//		�v���C���[�̃A�j���[�V����
	m_playerAnimation->Execute(0.0f, { 0.5f, -2.0f, 1.05f },
		{ 180.0f, 0.0f }, 2.5f);

	//		�X�V����
	m_iState->Update();
}

void TitleSelectManager::Render()
{
	m_screenEffectManager->ChangeRenderTarget();

	m_playerAnimation->Render();

	m_screenEffectManager->FirstRenderTarget();

	//		�w�i�̕`��
	m_backGroundMove->Render();

	//		�����_�[�^�[�Q�b�g�̕`��
	m_screenEffectManager->Render();

	//		�I���̕`��
	for (int i = 0, max = static_cast<int>((*m_information->GetDraowOder()).size()); i < max; ++i)
	{
		//		�I��UI�̕`��
		m_information->GetStandardShader()->Render((*m_information->GetDraowOder())[i]);
	}

	//		�X�y�[�X
	m_standardShader->Render(TitleInformation::TitleUIType::Space);

	//		�^�C�g�����S�̕`��
	m_standardShader->Render(TitleInformation::TitleUIType::TitleRogo);

	//		�`�揈��
	m_iState->Render();
}

void TitleSelectManager::Finalize()
{
	//		���̏�����
	m_information->Finalize();

	m_playerAnimation->Finalize();

	m_screenEffectManager->Finalize();

	m_backGroundMove->Finalize();

	m_standardShader.reset();
}

void TitleSelectManager::InputKey()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		W�{�^��OR�}�E�X�z�C�[����ŏ�Ɉړ�
	if (keyboard.IsKeyPressed(DirectX::Keyboard::S)|| 
		m_information->GetScrollWheel() > DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		�����ړ����������Ă���ꍇ�͏��������Ȃ�
		if (!m_information->GetKeyInput())
		{
			//		�L�[�������Ă���
			m_information->SetKeyInput(true);
			//		�ړ���������i��j
			m_information->SetDirection(true);

			//		�I�����ʉ�
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		m_information->SetScrollWheel(DirectX::Mouse::Get().GetState().scrollWheelValue);
	}

	//		S�{�^��OR�}�E�X�z�C�[�������ŉ��Ɉړ�
	if (keyboard.IsKeyPressed(DirectX::Keyboard::W) ||
		m_information->GetScrollWheel() < DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		�����ړ����������Ă���ꍇ�͏��������Ȃ�
		if (!m_information->GetKeyInput())
		{
			//		�L�[�������Ă���
			m_information->SetKeyInput(true);
			//		�ړ���������i���j
			m_information->SetDirection(false);

			//		�I�����ʉ�
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		//		�z�C�[���̒l���X�V����
		m_information->SetScrollWheel(DirectX::Mouse::Get().GetState().scrollWheelValue);
	}
}

void TitleSelectManager::CreateStandardShader()
{
	//		�^�C�g��UI�}�l�[�W���[�̐���
	m_standardShader = std::make_unique<StandardShader<TitleInformation::TitleUIType>>();

	//		�^�C�g��UI�}�l�[�W���̏�����
	m_standardShader->Initialize();

	//		�^�C�g�����S�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/TitleRogo.png",
		m_information->TITLE_POINT, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::TitleRogo);

	//		Play�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		m_information->CENTER_POINT, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::Play);

	//		End�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		m_information->UP_POINT , { m_information->MIN_SCALE,
		 m_information->MIN_SCALE },
		TitleInformation::TitleUIType::End);

	//		Setting�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		m_information->UNDER_POINT, { m_information->MIN_SCALE,
		 m_information->MIN_SCALE },
		TitleInformation::TitleUIType::Setting);

	//		Space�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/Space.png",
		m_information->SPACE_PLAY, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::Space);

	//		W�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/W.png",
		m_information->W_END, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::W);

	//		A�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/A.png",
		m_information->A_SETTING, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::A);
}

void TitleSelectManager::ChangeState
(TitleInformation::State state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I������������
	m_iState->Finalize();

	//		��Ԃ�؂�ւ���
	m_state = state;

	//		��Ԃ�؂�ւ���
	//m_iState = m_stateInformation[m_state].get();
	m_iState = (*m_information->GetStateInformation())[m_state].get();

	//		�V������Ԃ̏���������������
	m_iState->Initialize();
}