/*
* @file		GameStart.cpp
* @brief	�Q�[���X�^�[�g�}�l�[�W���[
* @author	Morita
* @date		2024/10/20
*/

#include "pch.h"

#include "GameStart.h"

GameStart::GameStart(GameManager* gameManager, UIManager* uiManager)
	:
	m_gameManager(gameManager),
	m_uiManager(uiManager),
	m_elapsedTime(0.0f),
	m_stayTime(0.0f),
	m_numberUpdateFrequency(0.0f),
	m_numberElapsedTime(0.0f),
	m_limitTime(0.0f),
	m_limitJudgement(false),
	m_numberTime(0.0f),
	m_numberStayTime(0.0f),
	m_threeCountNumber(3),
	m_threeCountElapsedTime(0.0f),
	m_endJudgement(false),
	m_numberSizeTime(0.0f)
{
}

GameStart::~GameStart()
{
}

void GameStart::Initialize()
{
	m_stayTime = 0.0f;
	m_elapsedTime = 0.0f;
	m_numberUpdateFrequency = 0.0f;
	m_numberElapsedTime = 0.0f;
	m_threeCountNumber = 3;
	m_threeCountElapsedTime = 0.0f;
	m_endJudgement = false;
	m_limitJudgement = false;
	m_numberSizeTime = 0.0;
	m_numberStayTime = 0.0f;
	m_numberTime = 0.0f;

	m_limitTime = m_gameManager->GetLimitTime();

	m_numberRender = std::make_unique<UIRenderManager>();

	//		�����V�F�[�_�[�̍쐻
	m_numberRender->Create(L"Resources/Texture/UI/GameStart/number.png",
		L"Resources/Shader/UI/Number/NumberVS.cso",
		L"Resources/Shader/UI/Number/NumberGS.cso",
		L"Resources/Shader/UI/Number/NumberPS.cso",
		m_constBuffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
}

void GameStart::Update()
{
	if (m_endJudgement) return;

	if (!m_gameManager->FlagJudgement(GameManager::StartLimitView)) return;

	//		����̑ҋ@����
	if (m_stayTime < 0.5f)
	{
		m_stayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		return;
	}

	//		�^�C���胊�~�b�g�̈ړ�����
	if (TimeLimitMove()) return;

	//		�^�C�����~�b�g�^�C�������_������
	if (TimeLimitNumberRandom()) return;

	//		�ԍ��T�C�Y���ԏ���
	if (NumberSizeTime()) return;

	//		�ҋ@����
	if (m_numberStayTime < 0.5f)
	{
		m_numberStayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		return;
	}

	//		�X���[�J�E���g�̏���
	ThreeCountProcess();
}

void GameStart::Render()
{
	if (m_endJudgement) return;

	if (!m_gameManager->FlagJudgement(GameManager::StartLimitView)) return;

	NumberView();

	if (ThreeCountView()) return;

	m_uiManager->GetStandardShader()->Render(UIManager::GameStartTimeLimit);
}

void GameStart::Finalize()
{
	m_stayTime = 0.0f;
	m_elapsedTime = 0.0f;
	m_numberUpdateFrequency = 0.0f;
	m_numberElapsedTime = 0.0f;
	m_threeCountNumber = 3;
	m_threeCountElapsedTime = 0.0f;
	m_endJudgement = false;
	m_limitJudgement = false;
	m_numberSizeTime = 0.0;
	m_numberRender.reset();
}

void GameStart::NumberView()
{
	if (m_elapsedTime < 1.0f)
	{
		return;
	}

	if (m_numberStayTime > 0.5f)
	{
		return;
	}

	DirectX::SimpleMath::Vector2 windowSize = LibrarySingleton::GetInstance()->GetScreenSize();

	float length = 330.0f;

	float length2 = 130.0f;

	float lengthY = 50.0f;

	(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::GameStartTimeTen].position = { 0.0f, lengthY };
	m_uiManager->GetStandardShader()->Render(UIManager::GameStartTimeTen);

	//		�\���P��
	m_numberRender->SetPosition({ windowSize.x / 2.0f - length, windowSize.y / 2.0f + lengthY });
	m_constBuffer.number = { static_cast<float>(m_number / 60 / 10), 0.0f, 0.0f, 0.0f };

	//		�`��
	m_numberRender->Render(m_constBuffer);

	//		���P��
	m_numberRender->SetPosition({ windowSize.x / 2.0f - length2, windowSize.y / 2.0f + lengthY });
	m_constBuffer.number = { static_cast<float>(m_number / 60 % 10), 0.0f, 0.0f, 0.0f };

	//		�`��
	m_numberRender->Render(m_constBuffer);

	//		�\�b
	m_numberRender->SetPosition({ windowSize.x / 2.0f + length2, windowSize.y / 2.0f + lengthY });
	m_constBuffer.number = { static_cast<float>(m_number % 60 / 10), 0.0f, 0.0f, 0.0f };

	//		�`��
	m_numberRender->Render(m_constBuffer);

	//		�b
	m_numberRender->SetPosition({ windowSize.x / 2.0f + length, windowSize.y / 2.0f + lengthY });
	m_constBuffer.number = { static_cast<float>(m_number % 60 % 10), 0.0f, 0.0f, 0.0f };

	//		�`��
	m_numberRender->Render(m_constBuffer);
}

bool GameStart::ThreeCountView()
{
	//		���ԑҋ@���Ԃ�0.5�ȉ��̏ꍇ���������Ȃ�
	if (m_numberStayTime < 0.5f) return false;

	//		�E�B���h�E�T�C�Y���󂯎��
	DirectX::SimpleMath::Vector2 windowSize = LibrarySingleton::GetInstance()->GetScreenSize();

	//		���W�𒆐S�ɂ���
	m_numberRender->SetPosition({ windowSize.x / 2.0f, windowSize.y / 2.0f });

	//		�T�C�Y��ύX����
	m_numberRender->SetSize({ 1.5f, 1.5f });
	
	//		�����̕ύX
	m_constBuffer.number = { static_cast<float>(m_threeCountNumber), 0.0f, 0.0f, 0.0f };

	//		�`��
	m_numberRender->Render(m_constBuffer);

	return true;
}

bool GameStart::TimeLimitMove()
{
	//		�o�ߎ��Ԃ�1�b�ȏ�̏ꍇ���������Ȃ�
	if (m_elapsedTime >= 1.0f) return false;

	//		�o�ߎ���
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	float move = 0.0f;

	//		��b�ȏ�ɂȂ�Ȃ��悤�ɂ���
	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	//		�C�[�W���O
	if (m_elapsedTime == 1.0f)
	{
		move = 1.0f;
	}
	else
	{
		move = 1.0f - pow(2.0f, -10.0f * m_elapsedTime);
	}

	//		���[�v���g���ړ�������
	(*m_uiManager->GetStandardShader()->GetUIInformation())[UIManager::GameStartTimeLimit].position =
	{ 0.0f, Library::Lerp(0.0f, -200.0f, move) };

	return true;
}

bool GameStart::TimeLimitNumberRandom()
{
	if (m_limitJudgement) return false;

	//		�o�ߎ���
	m_numberElapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 1.5f;

	//		�X�V���Ԃ��o�ߎ��Ԃ��傫���ꍇ
	if (m_numberElapsedTime > m_numberUpdateFrequency)
	{
		//		��敪�̒l�𑫂�
		m_numberUpdateFrequency += (m_numberElapsedTime * m_numberElapsedTime);

		//		�����Ŕԍ����o��
		m_number = static_cast<int>(LibrarySingleton::GetInstance()->Random(0.0f, 9999.0f));

		//		�o�ߎ��Ԃ����Z�b�g����
		m_numberElapsedTime = 0.0f;

		//		�X�V���Ԃ����ʂ𒴂����ꍇ
		if (m_numberUpdateFrequency >= 0.7f)
		{
			//		�{���̎��Ԃɂ���
			m_number = static_cast<int>(m_limitTime);

			//		����ȏ㏈�������Ȃ�
			m_limitJudgement = true;
		}
	}

	return true;
}

void GameStart::ThreeCountProcess()
{
	m_threeCountElapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_threeCountElapsedTime > 1.0f)
	{
		m_threeCountNumber -= 1;

		m_threeCountElapsedTime = 0.0f;

		if (m_threeCountNumber == 0)
		{
			m_gameManager->TrueFlag(GameManager::GameStart);

			m_endJudgement = true;
		}
	}
}

bool GameStart::NumberSizeTime()
{
	if (m_numberSizeTime >= 1.0f) return false;

	m_numberSizeTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	m_numberSizeTime = Library::Clamp(m_numberSizeTime, 0.0f, 1.0f);

	float move = 0.0f;

	if (m_numberSizeTime == 1)
	{
		move = 1.0f;
	}
	else
	{
		move = 1.0f - pow(2.0f, -10.0f * m_numberSizeTime);
	}

	float size = Library::Lerp(1.0f, 1.05f, move);

	m_numberRender->SetSize({ size, size });

	return true;
}
