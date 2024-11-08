/*
* @file		PlayerCamera.cpp
* @brief	�v���C���[�̃J����
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayerWallWalkCamera.h"

PlayerWallWalkCamera::PlayerWallWalkCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_time(0.0f)
{
}

PlayerWallWalkCamera::~PlayerWallWalkCamera()
{
}

void PlayerWallWalkCamera::Initialize()
{
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_playerCameraManager->GetInformation()->SetCameraAngleMin(-20.0f);
}

void PlayerWallWalkCamera::Update()
{
	if (m_time < 1.0f)
	{
		//		�o�ߎ��� ���@�T
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 5.0f;

		//		��b�ȏ�ɂȂ�Ȃ��悤�ɂ���
		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		float angle = 0;
		float radian = 0;

		//		�J�����p�x�ƈړ��p�x���󂯎��
		RadianConversion(&angle, &radian);

		//		�J�����̊p�x��ݒ肷��
		m_playerCameraManager->GetInformation()->SetAngle({
			Library::Lerp(angle, radian, m_time),
			m_playerCameraManager->GetInformation()->GetAngle().y });
	}
	else
	{
		//		�ʏ�̃J�����Ɠ�������
		m_playerCameraManager->CameraMove();
	}

	//		�f�O���[���烉�W�A���֍s��ɂ���
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().x));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::
		CreateRotationX(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().y));

	//		�����Ă���p�x�ɂ���
	DirectX::SimpleMath::Matrix rotation = matrixY * matrixX;

	//		�J�������W
	DirectX::SimpleMath::Vector3 position = m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		���_����
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), rotation.Invert());


	//		�^�[�Q�b�g�Ƀv���C���[�̍��W�𑫂�
	target += m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	DirectX::SimpleMath::Vector3 directin2 = m_playerCameraManager->GetPlayerInformationCamera()->GetWallWalkNormalize();

	float length2 = m_playerCameraManager->GetPlayerInformationCamera()->GetHeadMove() / 5.0f;

	directin2 = DirectX::SimpleMath::Vector3::Lerp(DirectX::SimpleMath::Vector3::Zero, directin2 * 0.1f, length2);

	directin2.y = Library::Lerp(1.0f, 0.9f, length2);

	//		�A�b�v�x�N�g��
	DirectX::SimpleMath::Vector3 up = directin2;

	//		�r���[�s����쐬
	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::CreateLookAt
	(position, target, up);

	m_playerCameraManager->GetInformation()->SetEye(position);
	m_playerCameraManager->GetInformation()->SetTarget(target);
	m_playerCameraManager->GetInformation()->SetUp(up);

	//		�����x�N�g����ݒ肷��
	m_playerCameraManager->GetInformation()->SetViewVelocity(target - position);

	//		�r���[�s���ݒ肷��
	LibrarySingleton::GetInstance()->SetView(view);

	//		�����J�����ړ��ʂ��O�ȉ��̏ꍇ
	if (m_playerCameraManager->GetPlayerInformationCamera()->GetHeadMove() <= 0.0f)
	{
		//		�v���C���[�J�����ɐ؂�ւ���
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->CameraType::Standard);
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

void PlayerWallWalkCamera::Finalize()
{
	m_time = 0.0f;
}

void PlayerWallWalkCamera::RadianConversion(float* cameraangle, float* velocityRadian)
{
	int radian = static_cast<int>(DirectX::XMConvertToDegrees(
		atan2(m_playerCameraManager->GetPlayerInformationCamera()->GetDirection().z,
			m_playerCameraManager->GetPlayerInformationCamera()->GetDirection().x)));


	//		�J�����̊p�x���󂯎��
	int angle = static_cast<int>(m_playerCameraManager->GetInformation()->GetAngle().x);

	//		�͈͂�0~�R�U�O�ɂ���
	radian = (radian - 90) % 360;
	angle %= 360;

	//		�O�ȉ��̏ꍇ360�𑫂����̐��ɂ���
	if (angle < 0.0f) { angle += 360; }
	if (radian < 0.0f) { radian += 360; }

	//		�ŒZ�����ňړ����邽�߁i+ -�j(- +)�̎�(+ -)�̕���360�𑫂�
	if (radian < 90 && angle > 270)
	{
		radian += 360;
	}
	else if (angle < 90.0f && radian > 270)
	{
		angle += 360;
	}

	*cameraangle = static_cast<float>(angle);
	*velocityRadian = static_cast<float>(radian);
}
