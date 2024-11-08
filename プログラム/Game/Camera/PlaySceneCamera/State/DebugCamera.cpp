/*
* @file		DebugCamera.cpp
* @brief	�f�o�b�N�J����
* @author	Morita
* @date		2024/04/23
*/

#include "pch.h"

#include "DebugCamera.h"

#include "Library/Library.h"

DebugCamera::DebugCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager)
{
	//		�}�E�X�𑊑Έʒu�ɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	//		�}�E�X�̃t�H�[���`�����Z�b�g����
	DirectX::Mouse::Get().ResetScrollWheelValue();
}

DebugCamera::~DebugCamera()
{
}

void DebugCamera::Initialize()
{
}

void DebugCamera::Update()
{
	m_playerCameraManager->CameraMove();

	//		�s��ɂ���
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().x));
	DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::
		CreateRotationX(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().y));

	DirectX::SimpleMath::Matrix rt = rotY * rotX;

	//		�J�����̍��W
	DirectX::SimpleMath::Vector3 eye = {0.0f, 1.0f, 1.0f};

	DirectX::SimpleMath::Vector3 up = { 0.0f, 1.0f, 0.0f };

	//		�������Ă���ꏊ�𒆐S�ɉ�]����悤�ɂ���
	eye = DirectX::SimpleMath::Vector3::Transform(eye, rt.Invert());

	//		�����_����̋���
	eye *= (5.0f - 0.0f / 100.0f);

	up = DirectX::SimpleMath::Vector3::Transform(up, rt.Invert());

	//		�^�[�Q�b�g�̍��W�𑫂�
	eye += m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		�^�[�Q�b�g�̍��W��ݒ肷��
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3
				(m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight().x,
				 m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight().y + 1.5f,
				 m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight().z);

	//		�r���[�s���ݒ肷��
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::
		CreateLookAt(eye, target, up));
}

void DebugCamera::Finalize()
{
}