/*
* @file		ResultManager.cpp
* @brief	���U���g�}�l�[�W���[
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultManager.h"

#include "State/ResultStart.h"
#include "State/ResultNumberMove.h"
#include "State/ResultEvaluation.h"
#include "State/ResultStay.h"
#include "State/ResultEnd.h"

ResultManager::ResultManager()
	:
	m_score(0),
	m_time(0),
	m_deathCount(0),
	m_iState(),
	m_rotation(0.0f),
	m_state{},
	m_menuUseJudgement(false)
{
	Generation();
}

ResultManager::~ResultManager()
{
}

void ResultManager::Initialize(int score, int time, int deathCount)
{
	m_score = score;
	m_time = time;
	m_deathCount = deathCount;

	//		�����㏸�V�F�[�_�[�̏�����
	m_riseNumber->Initialize(m_deathCount, m_time, m_score);

	//		�X�N���[���G�t�F�N�g�̏�����
	m_screenEffectManager->Initialize();

	//		�v���C���[�̃A�j���[�V����������
	m_playerAnimation->Initialize();

	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	CreateStandardShader();

	//		�w�i�̏�����
	m_backGroundMove->Initialize();

	//--
	//	�t�F�[�h��������
	//--

	//		�t�F�[�h�`��̍쐻
	m_fade = std::make_unique<UIRenderManager>();

	//		�o�b�t�@
	ResultInformation::ConstBuffer buffer = m_information->GetBuffer();

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

	//		������
	m_information->Initialize(m_shader.get(), m_riseNumber.get(),
		m_fade.get(), m_backGroundMove.get(),
		m_screenEffectManager.get(),
		m_playerAnimation.get());

	//		������Ԃ�������
	m_state = State::Start;

	//		������Ԃ�ݒ肷��
	m_iState = m_stateInformation[m_state].get();

	//		��Ԃ�����������
	m_iState->Initialize();
}

void ResultManager::Generation()
{
	//		�w�i�̐���
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		�����㏸�V�F�[�_�[�̐���
	m_riseNumber = std::make_unique<RiseNumberShader>();

	//		�v���C���[�̃A�j���[�V�����̍쐻
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Result);

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[�̍쐻
	m_screenEffectManager = std::make_unique<ScreenEffectManager>(ScreenEffectManager::ResultScene, nullptr);

	//		���𐶐�����
	m_information = std::make_unique<ResultInformation>();

	//		��Ԃ��쐬����
	CreateState();
}

void ResultManager::Update()
{
	//		��Ԃ̍X�V
	m_iState->Update();

	//		�v���C���[�̉�]
	m_rotation += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->PLAYER_ROTATION_SPEED;

	//		�v���C���[�̃A�j���[�V����
	m_information->GetAnimation()->Execute(0.0f, {3.9f, 1.1f, 8.0f},
		{m_rotation + 180.0f, 0.0f}, m_information->PLAYER_HEIGHT);
}

void ResultManager::Render()
{
	//		�����_�[�^�[�Q�b�g�̕ύX
	m_information->GetScreenEffect()->ChangeRenderTarget();

	//		�v���C���[�̕`��(���C���[)
	m_information->GetAnimation()->Render();

	//		�����_�[�^�[�Q�b�g��߂�
	m_information->GetScreenEffect()->FirstRenderTarget();

	//		�ړ��w�i�̕`��
	m_information->GetBackGround()->Render();

	//		�w�i�̕`��(UI)
	m_information->GetStandardShader()->Render(ResultInformation::ResultUIType::Back);

	//		�v���C���̔w�i
	m_information->GetStandardShader()->Render(ResultInformation::ResultUIType::PlayerBack);

	//		�����_�[�^�[�Q�b�g�̕`��
	m_information->GetScreenEffect()->Render();

	//		��Ԃ̕`��
	m_iState->Render();
}

void ResultManager::Finalize()
{
	m_information->GetRiseNumber();

	m_information->Finalize();

	m_riseNumber->Finalize();

	m_backGroundMove->Finalize();

	m_playerAnimation->Finalize();

	m_screenEffectManager->Finalize();

	m_shader.reset();

	m_fade.reset();

	m_rotation = 0.0f;
}

void ResultManager::CreateState()
{
	//		��Ԃ𐶐�����
	m_stateInformation.insert({State::Start, std::make_unique<ResultStart>(this)});
	m_stateInformation.insert({ State::NumberMove, std::make_unique<ResultNumberMove>(this) });
	m_stateInformation.insert({ State::Evaluation, std::make_unique<ResultEvaluation>(this) });
	m_stateInformation.insert({ State::Stay, std::make_unique<ResultStay>(this) });
	m_stateInformation.insert({ State::End, std::make_unique<ResultEnd>(this) });
}

void ResultManager::AnimationSkip()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�}�E�X�̎擾
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Space�܂��͍��N���b�N���������ꍇ��������
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		��Ԃ�؂�ւ���(�ҋ@���)
		m_iState = m_stateInformation[State::Stay].get();
	}
}

void ResultManager::CreateStandardShader()
{
	//		���U���gUI�}�l�[�W���[�̐���
	m_shader = std::make_unique<StandardShader<ResultInformation::ResultUIType>>();

	//		����������
	m_shader->Initialize();

	//		�w�i�摜
	m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ResultBack.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f },
		ResultInformation::ResultUIType::Back);

	//		�X�R�A�ɂ���ĕ]����ς���
	if (m_information->SCORE_A < m_score)
	{
		//		A�]���̐���
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreA.png",
			m_information->SCORE_POSITION, { 0.0f, 0.0f },
			ResultInformation::ResultUIType::EvaluationUI);
	}
	else if (m_information->SCORE_B < m_score)
	{
		//		B�]���̐���
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreB.png",
			m_information->SCORE_POSITION, { 0.0f, 0.0f },
			ResultInformation::ResultUIType::EvaluationUI);
	}
	else
	{
		//		C�]���̐���
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreC.png",
			m_information->SCORE_POSITION, { 0.0f, 0.0f },
			ResultInformation::ResultUIType::EvaluationUI);
	}

	//		���̃V�[���U���̐���
	m_shader->CreateUIInformation(L"Resources/Texture/UI/GameOver/button.png",
		m_information->NEXT_SCENE, { 1.0f, 1.0f },
		ResultInformation::ResultUIType::Button);

	//		�v���C���̔w�i�̐���
	m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/PlayerBack.png",
		{-300.0f, -100.0f}, {1.0f, 1.0f},
		ResultInformation::ResultUIType::PlayerBack);
}

void ResultManager::BackGroundUpdate()
{
	//		�w�i�̍X�V
	m_information->GetBackGround()->Update();
}

void ResultManager::ChangeState(State state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I������������
	m_iState->Finalize();

	m_state = state;

	//		��Ԃ�؂�ւ���
	m_iState = m_stateInformation[state].get();

	//		�V������Ԃ̏���������������
	m_iState->Initialize();
}
