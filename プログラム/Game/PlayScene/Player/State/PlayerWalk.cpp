/*
* @file		PlayerWalk.cpp
* @brief	�v���C���[�̕������
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerWalk.h"

#include "../Player.h"

PlayerWalk::PlayerWalk(Player* player)
	:
	m_player(player),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_speed(0.0f),
	m_accelerationJudgement(false)
{
}

PlayerWalk::~PlayerWalk()
{
}

void PlayerWalk::Initialize()
{
	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		���݂̑��x���󂯎��
	m_speed = m_player->GetInformation()->GetAcceleration().Length();

	//		�������x���x���ꍇ�͕������x���ő呬�x�ɂ���
	if (m_speed < m_player->GetInformation()->GetWalkSpeed())
	{
		//		��������������
		m_accelerationJudgement = true;
	}

	//		�A�j���[�V�����������
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Walk);
}

void PlayerWalk::Update()
{
	//		�ړ�����
	MoveProcessing();

	//		���b�V���Ɠ����������̏���
	m_player->GetCommonProcessing()->Gravity();
}

void PlayerWalk::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	if (!m_player->GetCommonProcessing()->FloorMeshHitJudgement())
	{
		//		��Ԃ�J�ڂ���(����)
		m_player->ChangeState(m_player->PlayerState::Fall);
	}

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());
	
	//		������
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerWalk::Animation()
{
	//		�����A�j���[�V����
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerWalk::Render()
{
}

void PlayerWalk::Finalize()
{
	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_speed = 0.0f;

	m_accelerationJudgement = false;
}

void PlayerWalk::MoveProcessing()
{
	//		�L�[�������Ă��邩�ǂ���
	m_keyInputJudgement = false;

	//		�ړ��������
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//		�ړ�����������󂯎��
	direction = m_player->GetCommonProcessing()->Direction(&m_keyInputJudgement);

	//		���K��
	direction.Normalize();

	//		�L�[��������Ă����Ԃ̏ꍇ
	if (m_keyInputJudgement)
	{
		//		�ړ����������ݒ肷��
		m_player->GetInformation()->SetDirection(direction);
	}

	//		���������ɂ��邩�ǂ���
	if (m_accelerationJudgement)
	{
		AccelerationProcess();
	}

	//		�����x���v�Z����
	DirectX::SimpleMath::Vector3 accelaration = m_player->GetCommonProcessing()->MoveDirection(
		m_player->GetInformation()->GetDirection()) * m_speed;

	//		�����x��ݒ肷��
	m_player->GetInformation()->SetAcceleration(accelaration);

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration() * LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWalk::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		�L�[��������Ă��Ȃ��ꍇ
	if (!m_keyInputJudgement)
	{
		//		��Ԃ�J�ڂ���(�ҋ@���)
		m_player->ChangeState(m_player->PlayerState::Stay);
	}

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	DirectX::Keyboard::State keyState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();
	
	//		space�ŃW�����v
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space)&&
		m_player->GetInformation()->GetJumpJudgement())
	{
		//		��Ԃ�؂�ւ���(�W�����v)
		m_player->ChangeState(m_player->PlayerState::Jump);
	}

	//		�S�[�������Ă��邩�ǂ���
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		��Ԃ�؂�ւ���i�S�[���j
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	//		���C���[���Ԃ��Ƃ��ł��邩�ǂ���
	m_player->GetCommonProcessing()->WireActionJudgement();

	//		Control�ł��Ⴊ��
	if (keyState.IsKeyDown(DirectX::Keyboard::LeftControl))
	{
		if (m_player->GetInformation()->GetAcceleration().Length() < m_player->GetInformation()->GetCrouchingSpeed())
		{
			//		��Ԃ�؂�ւ���(����)
			m_player->ChangeState(m_player->PlayerState::Walk);
		}
		else
		{
			//		��Ԃ�؂�ւ���(�X���C�f�B���O)
			m_player->ChangeState(m_player->PlayerState::Sliding);
		}
	}

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift)
		&& keyState.IsKeyDown(DirectX::Keyboard::W))
	{
		//		�_�b�V���ł��邩�ǂ���
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		��Ԃ�؂�ւ���(�_�b�V��)
			m_player->ChangeState(m_player->PlayerState::Dash);
		}
	}
}

void PlayerWalk::AccelerationProcess()
{
	//		���x�ɉ����x�𑫂�
	m_speed += ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�������x�𒴂����ꍇ���������������I������
	if (m_speed > m_player->GetInformation()->GetWalkSpeed())
	{
		//		���x��������x�ɂ���
		m_speed = m_player->GetInformation()->GetWalkSpeed();

		//		���������̏I���t���O
		m_accelerationJudgement = false;
	}
}
