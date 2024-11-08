/*
* @file		PlayerStartCamera.h
* @brief	�v���C���[�X�^�[�g�J����
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "PlayerStartCamera.h"

PlayerStartCamera::PlayerStartCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_time(0.0f),
	m_firstViewJudgement(true)
{
}

PlayerStartCamera::~PlayerStartCamera()
{
}

void PlayerStartCamera::Initialize()
{
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	//		�Q�[���X�^�[�g�t���O���I�t�ɂ���
	m_playerCameraManager->GetGameManager()->FalseFlag(GameManager::GameStart);

	if (!m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::StartLimitView))
	{
		m_firstViewJudgement = true;
	}
}

void PlayerStartCamera::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	float move = 1.0f - pow(1.0f - m_time, 4.0f);

	//		�f�O���[���烉�W�A���֍s��ɂ���
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetStartDirection()));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::
		CreateRotationX(DirectX::XMConvertToRadians(Library::Lerp(-40.0f, 0.0f, move)));

	//		�����Ă���p�x�ɂ���
	DirectX::SimpleMath::Matrix rotation = matrixY * matrixX;

	//		�J�������W
	DirectX::SimpleMath::Vector3 position = m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		���_����
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), rotation.Invert());

	//		�^�[�Q�b�g�Ƀv���C���[�̍��W�𑫂�
	target += m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		�A�b�v�x�N�g��
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		�r���[�s���ݒ肷��
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	(position, target, up));

	m_playerCameraManager->GetInformation()->SetEye(position);
	m_playerCameraManager->GetInformation()->SetTarget(target);
	m_playerCameraManager->GetInformation()->SetUp(up);

	//		�����x�N�g����ݒ肷��
	m_playerCameraManager->GetInformation()->SetViewVelocity(target - position);

	if (m_time >= 1.0f)
	{
		//		������Ԃ̏ꍇ
		if (m_firstViewJudgement)
		{
			m_playerCameraManager->GetGameManager()->TrueFlag(GameManager::StartLimitView);

			if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::GameStart))
			{
				m_firstViewJudgement = false;

				//		�X�^���_�[�h�J�����ɂ���
				m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Standard);
			}

			return;
		}

		//		�X�^���_�[�h�J�����ɂ���
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Standard);

		//		�Q�[���X�^�[�g�t���O���I���ɂ���
		m_playerCameraManager->GetGameManager()->TrueFlag(GameManager::GameStart);
	}
}

void PlayerStartCamera::Finalize()
{
	m_time = 0.0f;

	m_playerCameraManager->GetInformation()->SetAngle({ m_playerCameraManager->GetStartDirection(), 0.0f});
}
