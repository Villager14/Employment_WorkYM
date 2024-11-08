/*
* @file		PlayerWire.cpp
* @brief	�v���C���[�̃��C���[���
* @author	Morita
* @date		2024/05/13
*/

#include "pch.h"

#include "PlayerWire.h"

#include "../Player.h"

PlayerWire::PlayerWire(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f),
	m_speed(0.0f),
	m_fallJudgement(false),
	m_length(0.0f),
	m_floorHitJudgement(false),
	m_wallHitJudgement(false),
	m_firstSpeed(0.0f),
	m_decelerationJudgement(false),
	m_accelerationSpeed(0.0f)
{
}

PlayerWire::~PlayerWire()
{
}

void PlayerWire::Initialize()
{
	//		���x�̏���������
	SpeedInitlaize();

	//		�ړ�����
	m_direction = m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition();

	m_direction.Normalize();

	m_player->GetInformation()->SetDirection({0.0f, 0.0f, 1.0f});

	//		�������Ԃ��O�ɂ���
	m_player->GetInformation()->SetFallTime(0.0f);

	//		����
	m_length = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		�A�j���[�V�������C���[�W�����v���
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Wire);

	//		�_�b�V�����ʉ����ʉ��̍Đ�
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::Wire);

	//		�Q�[���}�l�[�W���[�̃_�b�V���t���O��ON�ɂ���
	m_player->GetGameManager()->TrueFlag(GameManager::DashJudgement);
}

void PlayerWire::Update()
{
	//		�ړ�����
	MoveProcessing();

	//		�d�͏���
	m_player->GetCommonProcessing()->Gravity(true);
}

void PlayerWire::Move()
{
	//		�ǃ��b�V���̓����蔻��
	if (m_player->GetCommonProcessing()->WallMeshHitJudgement())
	{
		//		�e�ɓ������Ă���
		if (m_fallJudgement)m_wallHitJudgement = true;
	}

	//		���ɓ������Ă��邩
	if (m_player->GetCommonProcessing()->FloorMeshHitJudgement())
	{
		//		���ɓ������Ă���
		if (m_fallJudgement)m_floorHitJudgement = true;
	}
	
	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		������Ԃɂ��邩�ǂ���
	FallJudgement();

	//		������
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerWire::Animation()
{
	//		���C���[�A�j���[�V����
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerWire::Render()
{
}

void PlayerWire::Finalize()
{
	m_time = 0.0f;

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_wallHitJudgement = false;

	m_floorHitJudgement = false;

	m_fallJudgement = 0.0f;

	m_decelerationJudgement = false;

	//		�A�j���[�V�����ҋ@���
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Stay);

	//std::vector<WireObjectInformation>* m_wireInformation = m_player->GetWireObjectInformation();

	for (int i = 0; i < (*m_player->GetWireObjectInformation()).size(); ++i)
	{
		(*m_player->GetWireObjectInformation())[i].m_actionJudgement = false;
	}

	//		�Q�[���}�l�[�W���[�̃_�b�V���t���O��OFF�ɂ���
	m_player->GetGameManager()->FalseFlag(GameManager::DashJudgement);
}

void PlayerWire::MoveProcessing()
{
	//		������Ԃ����f����
	if (!m_fallJudgement) AttractProcess();
	else FallProcess();

	DirectX::SimpleMath::Vector3 velocity = m_direction * m_speed;

	m_player->GetInformation()->SetAcceleration(velocity);

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() + m_direction *
		m_speed * LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWire::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		���C���[�A�N�V�������ł��邩�ǂ������f����
	m_player->GetCommonProcessing()->WireActionJudgement();

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�L�[�{�[�h�X�e�[�g�̎擾
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift))
	{
		//		�_�b�V���ł��邩�ǂ���
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		��Ԃ�؂�ւ���(�_�b�V��)
			m_player->ChangeState(m_player->PlayerState::Dash);

			return;
		}
	}

	if (m_floorHitJudgement)
	{
		//		�ړ��L�[���������Ƃ�
		if (keyboardState.IsKeyDown(DirectX::Keyboard::W) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::A) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::S) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::D))
		{
			//		��Ԃ�؂�ւ���i����)
			m_player->ChangeState(m_player->PlayerState::Walk);
		}
		else
		{
			//		��Ԃ�؂�ւ���i�ҋ@)
			m_player->ChangeState(m_player->PlayerState::Stay);
		}
	}

	if (m_wallHitJudgement)
	{
		DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

		acceleation.Normalize();

		if (m_player->GetCollitionInformation()->GetMeshWallNormalize().size() == 0) return;

		float dot = m_player->GetCollitionInformation()->GetMeshWallNormalize()[0].Dot(acceleation);

		//		�v���C���[�����̊p�x�������Ă���ꍇ����������
		if (dot <= -0.2f && dot >= -0.9f)
		{
			//		�@����������
			m_player->GetPlayerInformationCollition()->SetWallWalkNormalize(
				(m_player->GetCollitionInformation()->GetMeshWallNormalize()[0]));

			//		��Ԃ�؂�ւ���(�Ǖ������)
			m_player->ChangeState(m_player->PlayerState::WallWalk);
		}	
	}
}

void PlayerWire::AttractProcess()
{
	if (!m_decelerationJudgement)AccelerationProcess();
	else DecelerationProcess();
}

void PlayerWire::AccelerationProcess()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * ACCELERATION_RATE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		���x�̑J��
	m_speed = Library::Lerp(m_firstSpeed, m_firstSpeed + MAX_SPEED, m_time);

	//		���݂̋���
	float nowLength = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		�J�n�������ƌ��݋����̊�����7�ȉ��̏ꍇ���������ɂ���
	if (nowLength / m_length <= ACCELERATION_RATE)
	{
		//		���������ɂ���
		m_decelerationJudgement = true;

		//		�������x�����݂̑��x�ɂ���
		m_accelerationSpeed = m_speed;
	}
}

void PlayerWire::DecelerationProcess()
{
	//		���݂̋���
	float nowLenght = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		����
	float ratio = nowLenght / m_length;

	m_speed = Library::Lerp(m_firstSpeed, m_accelerationSpeed, ratio);
}

void PlayerWire::FallProcess()
{
	//		�L�[�������Ă��邩�ǂ���
	bool keyInputJudgement = false;

	//		�ړ��������
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//		�ړ�����������󂯎��
	direction = m_player->GetCommonProcessing()->Direction(&keyInputJudgement);

	//		���K��
	direction.Normalize();

	//		�ړ����������ǉ�����
	m_direction += m_player->GetCommonProcessing()->MoveDirection(direction) * 0.7f * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		���K��
	m_direction.Normalize();

	//		���x���ő呬�x�ȏ�̏ꍇ
	if (m_speed >= m_player->GetInformation()->GetMaxSpeed())
	{
		//		�ő呬�x�ɂ���@
		m_speed = m_player->GetInformation()->GetMaxSpeed();
	}
}

void PlayerWire::FallJudgement()
{
	//		�v���C���[���猩�����C���[�I�u�W�F�N�g�̕��������߂�
	DirectX::SimpleMath::Vector3 direction = m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition();

	//		���K��
	direction.Normalize();

	//		����
	float dot2 = m_direction.Dot(direction);

	//		�v���C���[�̈ړ������ƌ��݂̕������ʂ̏ꍇ���������ɂ���
	if (dot2 < 0.0f)
	{
		m_fallJudgement = true;

		m_time = 0.0f;
	}
}

void PlayerWire::SpeedInitlaize()
{
	//		�����̎擾
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		�������x
	m_firstSpeed = m_player->GetInformation()->GetAcceleration().Length();

	//		�������x���������x�ȉ��̏ꍇ
	if (m_firstSpeed <= m_player->GetInformation()->GetWalkSpeed())
	{
		m_firstSpeed = m_player->GetInformation()->GetWalkSpeed();
	}

	m_speed = m_firstSpeed;
}
