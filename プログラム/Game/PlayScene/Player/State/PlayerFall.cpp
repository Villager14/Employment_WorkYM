/*
* @file		PlayerFall.cpp
* @brief	�v���C���[�̗������
* @author	Morita
* @date		2024/07/19
*/

#include "pch.h"

#include "PlayerFall.h"

#include "../Player.h"

PlayerFall::PlayerFall(Player* player)
	:
	m_player(player),
	m_firstHeight(0.0f),
	m_speed(0.0f),
	m_rayHitJudgement(false),
	m_keyInputJudgement(false)
{
}

PlayerFall::~PlayerFall()
{
}

void PlayerFall::Initialize()
{
	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		�A�j���[�V�����ҋ@���
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Fall);

	//		���݂̑��x���󂯎��
	m_speed = m_player->GetInformation()->GetAcceleration().Length();

	//		�J�����̉�]�ʂ��󂯎��
	m_cameraMatrix = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x));

}

void PlayerFall::Update()
{
	MoveProcess();

	//		���b�V���Ɠ����������̏���
	m_player->GetCommonProcessing()->Gravity();

}

void PlayerFall::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

			//		���������ꏊ���Ȃ���Ώ��������Ȃ�
	if (m_player->GetCollitionInformation()->GetFloorMeshHitPoint().size() != 0)
	{
		if (abs(m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y -
			m_player->GetInformation()->GetPlanPosition().y) < 1.0f)
		{
			DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPlanPosition();

			position.y = m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y;

			m_player->GetInformation()->SetPlanPosition(position);

			m_player->GetInformation()->SetFallTime(0.0f);

			m_rayHitJudgement = true;
		}
	}


	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		������
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerFall::Animation()
{
	//		�ҋ@�A�j���[�V����
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(), 
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}


void PlayerFall::Render()
{
}

void PlayerFall::Finalize()
{
	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_speed = 0.0f;

	m_rayHitJudgement = false;

	m_keyInputJudgement = false;
}

void PlayerFall::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�L�[�{�[�h�X�e�[�g�̎擾
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		���C���[�A�N�V���������邩�ǂ���
	if (m_player->GetCommonProcessing()->WireActionJudgement())
	{
		return;
	}

	//		���ɓ������Ă��鎞
	if (m_rayHitJudgement)
	{
		//		�L�[��������Ă��Ȃ��ꍇ
		if (!m_keyInputJudgement)
		{
			//		��Ԃ�J�ڂ���(�ҋ@���)
			m_player->ChangeState(m_player->PlayerState::Stay);
		}
		else if (keyboardState.IsKeyDown(DirectX::Keyboard::LeftControl))
		{
			//		��Ԃ�J�ڂ���(�X���C�f�B���O)
			m_player->ChangeState(m_player->PlayerState::Sliding);
		}
		else
		{
			//		��Ԃ�؂�ւ���(�������)
			m_player->ChangeState(m_player->PlayerState::Walk);
		}
	}

	//		�S�[�������Ă��邩�ǂ���
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		��Ԃ�؂�ւ���i�S�[���j
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	//		space�ŃW�����v
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space)&&
		m_player->GetInformation()->GetJumpJudgement())
	{
		//		��Ԃ�؂�ւ���(���Ⴊ��)
		m_player->ChangeState(m_player->PlayerState::Jump);

		return;
	}

	//		LeftControl�ł��Ⴊ��
	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftControl))
	{
		//		��Ԃ�؂�ւ���(���Ⴊ��)
		m_player->ChangeState(m_player->PlayerState::Crouching);

		return;
	}

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift)
		&& keyboardState.IsKeyDown(DirectX::Keyboard::W))
	{
		//		�_�b�V���ł��邩�ǂ���
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		��Ԃ�؂�ւ���(�_�b�V��)
			m_player->ChangeState(m_player->PlayerState::Dash);
		}
	}
}

void PlayerFall::MoveProcess()
{
	//		�L�[�������Ă��邩�ǂ���
	m_keyInputJudgement = false;

	//		�ړ��������
	DirectX::SimpleMath::Vector3 direction =
		DirectX::SimpleMath::Vector3::Zero;

	//		�ړ�����������󂯎��
	direction = m_player->GetCommonProcessing()->Direction(&m_keyInputJudgement);

	//		�ړ����������ݒ肷��
	m_player->GetInformation()->SetDirection(direction);

	DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

	acceleation += DirectX::SimpleMath::Vector3::Transform(
		direction, m_cameraMatrix.Invert()) * 60.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

	if (acceleation.Length() > m_speed)
	{
		acceleation.Normalize();

		acceleation *= m_speed;
	}

	m_player->GetInformation()->SetAcceleration(acceleation);

	DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPosition();

	position.y = m_player->GetInformation()->GetPlanPosition().y;

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(position +
		m_player->GetInformation()->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}
