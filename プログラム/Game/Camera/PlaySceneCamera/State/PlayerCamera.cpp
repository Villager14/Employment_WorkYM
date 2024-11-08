/*
* @file		PlayerCamera.cpp
* @brief	�v���C���[�̃J����
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayerCamera.h"

PlayerCamera::PlayerCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_shakingTime(0.0f),
	m_shakingRatio(0.0f),
	m_shakingSpeed(0.0f)
{
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Initialize()
{
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_playerCameraManager->GetInformation()->SetCameraAngleMin(m_playerCameraManager->GetInformation()->ANGLE_Y_MIN);
}

void PlayerCamera::Update()
{
	m_playerCameraManager->CameraMove();

	//		���݂̍��W
	m_position = m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//m_shakingTime = 0.0f;


	//		�f�O���[���烉�W�A���֍s��ɂ���
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().x));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().y));

	//		�����Ă���p�x�ɂ���
	DirectX::SimpleMath::Matrix rotation = matrixY * matrixX;

	//		���_����
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), rotation.Invert());

	//		�^�[�Q�b�g�Ƀv���C���[�̍��W�𑫂�
	target += m_position;

	//		�A�b�v�x�N�g��
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		�r���[�s���ݒ肷��
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	(m_position, target, up));

	m_playerCameraManager->GetInformation()->SetEye(m_position);
	m_playerCameraManager->GetInformation()->SetTarget(target);
	m_playerCameraManager->GetInformation()->SetUp(up);

	//		�����x�N�g����ݒ肷��
	m_playerCameraManager->GetInformation()->SetViewVelocity(target - m_position);

	//		�J������~�t���O��true�̎�
	if (m_playerCameraManager->GetPlayerInformationCamera()->GetCameraStop())
	{
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Stop);
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

void PlayerCamera::Finalize()
{
}

void PlayerCamera::ShakingView()
{
	//		���݂̍��W
	m_position = m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		�v���C���[�̑��x���󂯎��
	float playerSpeed = m_playerCameraManager->GetPlayerInformationCamera()->GetAcceleration().Length();

	//		���𓮂���������ݒ肷��
	m_shakingRatio = playerSpeed / m_playerCameraManager->GetPlayerInformationCamera()->GetMaxSpeed();

	//		���𓮂�������
	m_shakingSpeed = Library::Lerp(2.0f, 10.0f, m_shakingRatio);

	//		���𓮂�������
	m_shakingTime += LibrarySingleton::GetInstance()->GetElpsedTime() * m_shakingSpeed;

	//		�c�h��
	VerticalShaking();

	//		���h��
	HorizontalShaking();
	
}

void PlayerCamera::HorizontalShaking()
{
	DirectX::SimpleMath::Vector2 velocity = { m_playerCameraManager->GetInformation()->GetViewVelocity().x,
										m_playerCameraManager->GetInformation()->GetViewVelocity().z };

	velocity.Normalize();

	velocity = DirectX::SimpleMath::Vector2(velocity.y, -velocity.x);


	float move = (sinf(m_shakingTime) + 1.0f) / 2.0f;

	//		���̓����̕�
	float moveLength = Library::Lerp(0.0f, 0.2f, m_shakingRatio);


	velocity = DirectX::SimpleMath::Vector2::Lerp( DirectX::SimpleMath::Vector2(velocity.x, velocity.y) * moveLength,
										DirectX::SimpleMath::Vector2(velocity.x, velocity.y) * -moveLength,
										move);

	m_position.x += velocity.x;
	m_position.z += velocity.y;
}

void PlayerCamera::VerticalShaking()
{
	float move = (sinf(m_shakingTime * 2.0f) + 1.0f) / 2.0f;

	//		���̓����̕�
	float moveLength = Library::Lerp(0.0f, 0.4f, m_shakingRatio);

	m_position.y += Library::Lerp(-moveLength, moveLength, move);
}
