/*
* @file		PlayerCameraManager.cpp
* @brief	�v���C���[�̃J�����̃}�l�[�W���[
* @author	Morita
* @date		2024/05/08
*/

#include "pch.h"

#include "PlayerCameraManager.h"

PlayerCameraManager::PlayerCameraManager(GameManager* gameManager)
	:
	m_state{},
	m_playerInformation{},
	m_gameManager(gameManager),
	m_cameraType{},
	m_startDirection(0.0f),
	m_nowViewAngle(70.0f)
{
	//		�J�����̏���
	m_information = std::make_unique<PlayerCameraInformation>();

	//		�J�����̔h���N���X�̐���
	m_stateInformation.insert({ CameraType::Standard, std::make_unique<PlayerCamera>(this) });
	m_stateInformation.insert({ CameraType::Debug, std::make_unique<DebugCamera>(this) });
	m_stateInformation.insert({ CameraType::WallWalk, std::make_unique<PlayerWallWalkCamera>(this) });
	m_stateInformation.insert({ CameraType::Start, std::make_unique<PlayerStartCamera>(this) });
	m_stateInformation.insert({ CameraType::Stop, std::make_unique<PlayerCameraStop>(this) });
	m_stateInformation.insert({ CameraType::Death, std::make_unique<PlayerDeathCamera>(this) });
	m_stateInformation.insert({ CameraType::Goal, std::make_unique<PlayerGoalCamera>(this) });
}

PlayerCameraManager::~PlayerCameraManager()
{
}

void PlayerCameraManager::Initialize(PlayerInformation* playerInformation)
{
	m_playerInformation = playerInformation;

	/*
	*	����p70�x
	*/
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(m_information->GetViewAngle()), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

	//		�v���W�F�N�V�����s���ݒ肷��
	LibrarySingleton::GetInstance()->SetProj(proj);

	//		���̏�����
	m_information->Initialize();

	//		�������
	m_cameraType = CameraType::Start;

	//		������Ԃ�ݒ肷��
	m_state = m_stateInformation[m_cameraType].get();

	//		����������
	m_state->Initialize();

	//		��x�X�V�����Ă���(Effect�̈�)
	m_state->Update();
}

void PlayerCameraManager::Update()
{
	//		�J�����̍X�V����
	m_state->Update();

	ViewingAngle();
}

void PlayerCameraManager::Finalize()
{
	m_startDirection = 0.0f;
	m_information->Finalize();
}

void PlayerCameraManager::CameraMove()
{
	//		�}�E�X�̑��Έʒu����ړ��ʂ��o��
	float x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	float y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	DirectX::SimpleMath::Vector2 angle = m_information->GetAngle();

	//		�ړ���
	DirectX::SimpleMath::Vector2 move = DirectX::SimpleMath::Vector2::Zero;

	//		�J�����̈ړ��ʂ𑫂�
	move.x += x * m_information->GetCameraSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();
	move.y += -y * (m_information->GetCameraSpeed() / 2.0f) * LibrarySingleton::GetInstance()->GetElpsedTime();

	angle += move;

	//		���_�ړ��̐���
	angle.y = Library::Clamp(angle.y, m_information->GetCameraAngleMin(), m_information->ANGLE_Y_MAX);
	
	m_information->SetAngle(angle);
	m_information->SetCameraMove(move);

}

void PlayerCameraManager::ChangeState(CameraType type)
{
	//		���݂̓�����ԂȂ�s��Ȃ�
	if (type == m_cameraType) return;

	//		���݂̏�Ԃ̏I���������s��
	m_state->Finalize();

	//		�V������Ԃɏ㏑������
	m_cameraType = type;

	//		�V������Ԃɂ���
	m_state = m_stateInformation[m_cameraType].get();

	//		�V������Ԃ̏�����������
	m_state->Initialize();

}

void PlayerCameraManager::ViewingAngle()
{
	float time = Library::Clamp(((m_playerInformation->GetAcceleration().Length() - 30.0f) / 60.0f), 0.0f, 1.0f);

	float angle = Library::Lerp(0.0f, 30.0f, time);

	m_nowViewAngle = Library::Lerp(m_nowViewAngle, angle, 0.7f);

	float viewAnge = m_nowViewAngle + m_information->GetViewAngle();

	//		�r���[�s����쐬����
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(viewAnge), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

	//		�v���W�F�N�V�����s���ݒ肷��
	LibrarySingleton::GetInstance()->SetProj(proj);



	/*
	float time = Library::Clamp(((m_playerInformation->GetAcceleration().Length() - 30.0f) / 60.0f), 0.0f, 1.0f);

	float angle = Library::Lerp(0.0f, 30.0f, time);

	m_nowViewAngle = Library::Lerp(m_nowViewAngle, angle, 0.7f);

	float viewAnge = m_nowViewAngle + m_information->GetViewAngle();

	//		�r���[�s����쐬����
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(viewAnge), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

	//		�v���W�F�N�V�����s���ݒ肷��
	LibrarySingleton::GetInstance()->SetProj(proj);
	*/

}

void PlayerCameraManager::ViewAngleUpdate(PlayerInformation* playerInformation)
{
	m_playerInformation = playerInformation;

	float time = Library::Clamp(((m_playerInformation->GetAcceleration().Length() - 30.0f) / 60.0f), 0.0f, 1.0f);

	float move = time;

	float viewAnge = Library::Lerp(m_information->GetViewAngle(), m_information->GetViewAngle() + 20.0f, move);

	//		proj�s����쐬����
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(viewAnge), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
			LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

	//		�v���W�F�N�V�����s���ݒ肷��
	LibrarySingleton::GetInstance()->SetProj(proj);
}
