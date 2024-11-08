/*
* @file		PlayerStay.cpp
* @brief	�v���C���[�̑ҋ@���
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerStay.h"

#include "../Player.h"

PlayerStay::PlayerStay(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f)
{
}

PlayerStay::~PlayerStay()
{
}

void PlayerStay::Initialize()
{
	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		�A�j���[�V�����ҋ@���
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Stay);
}

void PlayerStay::Update()
{
	//		����
	Deceleration();

	//		���b�V���Ɠ����������̏���
	m_player->GetCommonProcessing()->Gravity();

}

void PlayerStay::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		������
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerStay::Animation()
{
	//		�ҋ@�A�j���[�V����
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(), 
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}


void PlayerStay::Render()
{
}

void PlayerStay::Finalize()
{
	m_time = 0.0f;

	m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3::Zero);

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);
}

void PlayerStay::Deceleration()
{
	//		����
	DirectX::SimpleMath::Vector3 acceleration = m_player->GetInformation()->GetAcceleration();

	//		����
	acceleration *= 0.8f;

	m_player->GetInformation()->SetAcceleration(acceleration);

	//		���x�ƈړ��ʂ��v�Z����
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration()
		* LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerStay::ChangeStateJudgement()
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

	//		�ړ��L�[���������Ƃ�
	if (keyboard.IsKeyPressed(DirectX::Keyboard::W) ||
		keyboard.IsKeyPressed(DirectX::Keyboard::A) ||
		keyboard.IsKeyPressed(DirectX::Keyboard::S) ||
		keyboard.IsKeyPressed(DirectX::Keyboard::D))
	{
		//		��Ԃ�؂�ւ���i����)
		m_player->ChangeState(m_player->PlayerState::Walk);

		return;
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
}
