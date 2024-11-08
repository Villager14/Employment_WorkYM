

#include "pch.h"

#include "SpeedLine.h"

SpeedLine::SpeedLine(UIManager* uiManager)
	:
	m_uiManager(uiManager),
	m_time(1.0f),
	m_frontTime(1.0f),
	frontFlag(false),
	m_speed(0.0f),
	m_backTime(0.0f)
{
}

SpeedLine::~SpeedLine()
{
}

void SpeedLine::Initialize()
{
	m_shader = std::make_unique<UIRenderManager>();

	//		��]�V�F�[�_�[�̍쐻
	m_shader->Create(L"Resources/Texture/UI/Speed/UISpeed.png",
		L"Resources/Shader/UI/SpeedLine/SpeedLineVS.cso",
		L"Resources/Shader/UI/SpeedLine/SpeedLineGS.cso",
		L"Resources/Shader/UI/SpeedLine/SpeedLinePS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	m_shader->LoadTexture(L"Resources/Texture/UI/Speed/Speed01.png", 1);

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	buffer.rotationMatrix = m_shader->GetRotationMatrix();

	m_frontTime = 1.0f;
	m_time = 1.0f + LINE_LENGTH;
}

void SpeedLine::Update()
{
	//		�_�b�V�������Ă��邩�ǂ���
	if (!m_uiManager->GetGameManager()->
		FlagJudgement(GameManager::DashJudgement)
		&& m_uiManager->GetPlayerInformation()->GetAcceleration().Length() < MINIMUM_SPEED)
	{
		if (m_frontTime < 1.0f)
		{
			m_frontTime = 1.0f;
			m_time = 1.0f + LINE_LENGTH;
			m_backTime = 0.0f;
		}

		return;
	}

	m_backTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;

	//		MINIMUM_SPEED�ȏ�MAXIMUM_SPEED�ȓ��ɂ���
	float val = Library::Clamp(m_uiManager->GetPlayerInformation()->GetAcceleration().Length(), MINIMUM_SPEED, MAXIMUM_SPEED);
	
	//		���C�̑��x�����߂�
	m_speed = Library::Lerp(RAY_SPEED_MIN, RAY_SPEED_MAX, (val - MINIMUM_SPEED) / (MAXIMUM_SPEED - MINIMUM_SPEED));

	//		�A���t�@�p���[�����߂�
	buffer.alphaPower = Library::Lerp(MIN_ALPHA_POWER, MAX_ALPHA_POWER, (val - MINIMUM_SPEED) / (MAXIMUM_SPEED - MINIMUM_SPEED));

	//		�o�ߎ���
	m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_speed;

	if (m_time <= 1.0f - LINE_LENGTH && frontFlag)
	{
		frontFlag = false;

		m_frontTime = 1.0f - LINE_LENGTH;
		m_time = 1.0f;
	}


	m_frontTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_speed;

	if (m_frontTime <= 0.0f)
	{
		m_frontTime = LINE_LENGTH;

		m_time = 1.0f;

		frontFlag = true;
	}


	//		�R���X�g�o�b�t�@�̎��Ԃ̍X�V
	buffer.time = { m_time, m_frontTime,
		static_cast<float>(frontFlag), 0.0f};
}

void SpeedLine::Render()
{
	//		�_�b�V�������Ă��邩�ǂ���
	if (!m_uiManager->GetGameManager()->
		FlagJudgement(GameManager::DashJudgement)
		&& m_uiManager->GetPlayerInformation()->GetAcceleration().Length() < MINIMUM_SPEED)
	{
		return;
	}

	buffer.backTime = m_backTime;

	//		UI�̕`��
	m_shader->Render(buffer);
}

void SpeedLine::Finalize()
{
	m_shader.reset();
}
