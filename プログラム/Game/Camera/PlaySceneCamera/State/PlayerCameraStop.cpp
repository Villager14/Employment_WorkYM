/*
* @file		PlayerCameraStop.cpp
* @brief	�v���C���[�����Ȃ��̃J����
* @author	Morita
* @date		2024/06/10
*/

#include "pch.h"

#include "PlayerCameraStop.h"

PlayerCameraStop::PlayerCameraStop(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager)
{
}

PlayerCameraStop::~PlayerCameraStop()
{
}

void PlayerCameraStop::Initialize()
{
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void PlayerCameraStop::Update()
{
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

	//		�v���C���[�̒�~���I�������Ƃ�
	if (!m_playerCameraManager->GetPlayerInformationCamera()->GetCameraStop())
	{
		//		�v���C���[�J�����ɐ؂�ւ���
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->CameraType::Standard);
	}

	//		�����J�����ړ��ʂ��O���傫��������
	if (m_playerCameraManager->GetPlayerInformationCamera()->GetHeadMove() > 0.0f)
	{
		//		�Ǒ���J�����ɐ؂�ւ���
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->CameraType::WallWalk);
	}

	//		���S���Ă���ꍇ
	if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::DeathJudgement))
	{
		//		���S�J�����ɂ���
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Death);
	}

	//		���̃V�[����I�񂾍�
	if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::EndJudgement))
	{
		//		�S�[���J�����ɂ���
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Goal);
	}
}

void PlayerCameraStop::Finalize()
{
}
