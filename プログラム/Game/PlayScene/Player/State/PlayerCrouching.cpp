/*
* @file		PlayerCrouching.cpp
* @brief	�v���C���[�̂��Ⴊ�ݏ��
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerCrouching.h"

#include "../Player.h"

PlayerCrouching::PlayerCrouching(Player* player)
	:
	m_player(player),
	m_firstHeight(0.0f),
	m_keyInputJudgement(false)
{
}

PlayerCrouching::~PlayerCrouching()
{
}

void PlayerCrouching::Initialize()
{
	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;
}

void PlayerCrouching::Update()
{
	//		�ړ�����
	MoveProcessing();

	//		���b�V���Ɠ����������̏���
	m_player->GetCommonProcessing()->Gravity();

}

void PlayerCrouching::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		���Ⴊ�ݍ����ɂ��鏈��
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,m_player->GetInformation()->GetCrouchingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerCrouching::Animation()
{
	if (m_keyInputJudgement)
	{
		//		�������
		m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->CrouchingWalk);

	}
	else
	{
		//		���Ⴊ�ݒ�~�A�j���[�V����
		m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->CrouchingStay);
	}

	//		���Ⴊ�ݕ����A�j���[�V����
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerCrouching::Render()
{
}

void PlayerCrouching::Finalize()
{
	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_firstHeight = 0.0f;
}

void PlayerCrouching::MoveProcessing()
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

		//		���x����
		SpeedProcessing();
	}
	else
	{
		m_player->GetInformation()->SetAcceleration(
			m_player->GetInformation()->GetAcceleration() * 0.8f);
	}

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(
		m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerCrouching::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�L�[�{�[�h�X�e�[�g�̎擾
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		�S�[�������Ă��邩�ǂ���
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		��Ԃ�؂�ւ���i�S�[���j
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	//		���C���[���Ԃ��Ƃ��ł��邩�ǂ���
	m_player->GetCommonProcessing()->WireActionJudgement();

	//		�L�[�𗣂����ꍇ
	if (keyboard.IsKeyReleased(DirectX::Keyboard::LeftControl))
	{
		//		�ړ��L�[��������Ă���ꍇ
		if (keyboardState.IsKeyDown(DirectX::Keyboard::W) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::A) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::S) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::D))
		{
			//		��Ԃ�J�ڂ���(�������)
			m_player->ChangeState(m_player->PlayerState::Walk);
		}
		else
		{
			//		��Ԃ�J�ڂ���(�ҋ@���)
			m_player->ChangeState(m_player->PlayerState::Stay);
		}
	}
}

void PlayerCrouching::SpeedProcessing()
{
	//		�����x���󂯎��
	DirectX::SimpleMath::Vector3 accelaration = m_player->GetInformation()->GetAcceleration();

	//		�����x�̏���
	accelaration += m_player->GetCommonProcessing()->MoveDirection(m_player->GetInformation()->GetDirection())
		* 2000.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		���������̑�����葁���Ȃ����ꍇ
	if (accelaration.Length() > m_player->GetInformation()->GetCrouchingSpeed())
	{
		//		���K��
		accelaration.Normalize();

		//		�����x�ɕ����̑������|����
		accelaration *= m_player->GetInformation()->GetCrouchingSpeed();
	}

	//		�����x��ݒ肷��
	m_player->GetInformation()->SetAcceleration(accelaration);

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(
		m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime()
	);
}