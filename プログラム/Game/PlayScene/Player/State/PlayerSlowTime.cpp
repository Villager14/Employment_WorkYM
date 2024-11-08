/*
* @file		PlayerSlowTime.cpp
* @brief	�v���C���[�̒ᑬ���ԏ��
* @author	Morita
* @date		2024/04/29
*/

#include "pch.h"

#include "PlayerSlowTime.h"

#include "../Player.h"

PlayerSlowTime::PlayerSlowTime(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f)
{
}

PlayerSlowTime::~PlayerSlowTime()
{
}

void PlayerSlowTime::Initialize()
{
	//		�ړ�����
	m_direction = m_player->GetCommonProcessing()->MoveDirection(m_player->GetInformation()->GetDirection());

	//		���Ԃ̑��x��ݒ肷��
	m_player->GetInformation()->SetTimeSpeed(0.1f);

	//		�����̎擾
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;
}

void PlayerSlowTime::Update()
{
	//		�o�ߎ���
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�ړ�����
	MoveProcessing();

	//		���b�V���Ɠ����������̏���
	//m_player->Gravity();
}

void PlayerSlowTime::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());
	
	//		������
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetPosition().y + m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerSlowTime::Animation()
{
}

void PlayerSlowTime::Render()
{
}

void PlayerSlowTime::Finalize()
{
	m_time = 0.0f;

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		���Ԃ̑��x��ݒ肷��
	m_player->GetInformation()->SetTimeSpeed(1.0f);

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		�O���Ƀ_�b�V��
	m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f));
}

void PlayerSlowTime::MoveProcessing()
{
	//		�L�[�{�[�hState�̎擾
	DirectX::Keyboard::State m_keyboard = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		�ړ��������
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::D))
	{
		direction.x += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::A))
	{
		direction.x += 1.0f;
	}

	float speed = 10.0f;

	//		�ړ��������
	DirectX::SimpleMath::Vector3 velocity = m_player->GetCommonProcessing()->MoveDirection(direction) * speed *
		LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�ړ��\��ꏊ
	m_player->GetInformation()->SetPlanPosition(velocity + m_player->GetInformation()->GetPosition());

}

void PlayerSlowTime::ChangeStateJudgement()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		space�ŃW�����v
	if (keyboard.IsKeyReleased(DirectX::Keyboard::LeftShift))
	{
		//		��Ԃ�؂�ւ���(�_�b�V�����)
		m_player->ChangeState(m_player->PlayerState::Dash);
	}

	if (m_time > 3.0f)
	{
		//		��Ԃ�؂�ւ���(�_�b�V�����)
		m_player->ChangeState(m_player->PlayerState::Dash);
	}
}
