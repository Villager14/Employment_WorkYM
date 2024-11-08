/*
* @file		PlayerGoalCamera.cpp
* @brief	�v���C���[�̃S�[���J����
* @author	Morita
* @date		2024/06/27
*/

#include "pch.h"

#include "PlayerGoalCamera.h"

PlayerGoalCamera::PlayerGoalCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_elapsedTime(0.0f),
	m_downElapsedTime(0.0f)
{
}

PlayerGoalCamera::~PlayerGoalCamera()
{
}

void PlayerGoalCamera::Initialize()
{
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_angle = m_playerCameraManager->GetInformation()->GetAngle();

	m_elapsedTime = 0.0f;

	m_downElapsedTime = 0.0f;
}

void PlayerGoalCamera::Update()
{
	CameraMove();

	//		�f�O���[���烉�W�A���֍s��ɂ���
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().x));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().y));

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
}

void PlayerGoalCamera::Finalize()
{
	//		�J�����̊p�x�����Z�b�g����
	m_playerCameraManager->GetInformation()->SetAngle(DirectX::SimpleMath::Vector2::Zero);

}

void PlayerGoalCamera::CameraMove()
{
	if (m_elapsedTime < 2.0f)
	{

		//		�o�ߎ���
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;


		if (m_elapsedTime <= 1.0f)
		{
			//		�J�����𕽍s�ɂ���
			m_playerCameraManager->GetInformation()->SetAngle({ m_angle.x ,Library::Lerp(m_angle.y, 0.0f, m_elapsedTime) });
		}
	}
	else
	{
		m_downElapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_downElapsedTime = Library::Clamp(m_downElapsedTime, 0.0f, 1.0f);

		//		��������
		m_playerCameraManager->GetInformation()->SetAngle({ m_angle.x ,Library::Lerp(0.0f, -50.0f, m_downElapsedTime) });
	}
}
