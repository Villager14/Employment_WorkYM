/*
* @file		PlayerSliding.cpp
* @brief	�v���C���[�̃X���C�f�B���O
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerSliding.h"

#include "../Player.h"

PlayerSliding::PlayerSliding(Player* player)
	:
	m_player(player),
	m_keyInputJudgement(false),
	m_firstSpeed(0.0f),
	m_speed(0.0f),
	m_slopeJudgement(false),
	m_decelerationSpeed(0.0f),
	m_firstHeight(0.0f),
	m_accelerationTime(0.0f)
{
}

PlayerSliding::~PlayerSliding()
{
}

void PlayerSliding::Initialize()
{
	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		�����̑��x
	m_speed = m_player->GetInformation()->GetAcceleration().Length() + INTIAL_VELOCITY;

	//		�������x
	m_decelerationSpeed = m_player->GetInformation()->GetAcceleration().Length() / 3.0f * 2.0f;

	//		
	SlopeJudgement();

	//		�X���C�f�B���O�����Ă����Ԃɂ���
	m_player->GetPlayerInformationCollition()->SetSlidingJudgement(true);

	//		����h�炷��Ԃɂ��Ȃ�
	m_player->GetInformation()->SetHeadShakingJudgement(false);

	//		�A�j���[�V�����ҋ@���
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Sliding);
}

void PlayerSliding::Update()
{

	//		�ړ�����
	MoveProcessing();

	//		���b�V���Ɠ����������̏���
	m_player->GetCommonProcessing()->Gravity();

}

void PlayerSliding::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		����h�炷��Ԃɂ��Ȃ�
	m_player->GetInformation()->SetHeadShakingJudgement(false);

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		������
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,m_player->GetInformation()->GetSlidngHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerSliding::Animation()
{
	//		�X���C�f�B���O�A�j���[�V����
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerSliding::Render()
{
	//		���x
	LibrarySingleton::GetInstance()->DebugFont(L"Speed", m_slopeJudgement, 0, 150);
}

void PlayerSliding::Finalize()
{
	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_firstSpeed = 0.0f;

	m_speed = 0.0f;

	m_slopeJudgement = false;

	//		�X���C�f�B���O�����Ă����Ԃɂ���
	m_player->GetPlayerInformationCollition()->SetSlidingJudgement(false);
}

void PlayerSliding::MoveProcessing()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		���ݍ₩�ǂ���
	SlopeJudgement();

	if (m_slopeJudgement)
	{
		//		�����x���󂯎��
		DirectX::SimpleMath::Vector3 m_acceleration = m_player->GetInformation()->GetAcceleration();

		m_acceleration.x += m_slidingVelocity.x * SLIDING_ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();
		m_acceleration.z += m_slidingVelocity.y * SLIDING_ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

		if (m_acceleration.Length() > 80.0f)
		{
			m_acceleration.Normalize();

			m_acceleration *= 80.0f;
		}

		m_player->GetInformation()->SetAcceleration(m_acceleration);

		//		���x����ɒB���Ă��邩���f����
		m_player->GetCommonProcessing()->SpeedUpperLimit();

		//		���x��ݒ肷��
		m_speed = m_player->GetInformation()->GetAcceleration().Length();

		//		�������x
		m_decelerationSpeed = m_player->GetInformation()->GetAcceleration().Length() * 1.5f;

		//		���W�ɐݒ肷��
		m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
			m_player->GetInformation()->GetAcceleration() *
			LibrarySingleton::GetInstance()->GetElpsedTime());

	}
	else
	{
		if (m_accelerationTime <= 0.0f)
		{
			//		���x��x������
			m_speed -= m_decelerationSpeed *
				LibrarySingleton::GetInstance()->GetElpsedTime();
		}
		else
		{
			m_accelerationTime -= LibrarySingleton::GetInstance()->GetElpsedTime();
		}

		//		�����x���󂯎��
		DirectX::SimpleMath::Vector3 m_acceleration = m_player->GetInformation()->GetAcceleration();

		//		���������𐳋K��
		m_acceleration.Normalize();

		//		���x���|����
		m_acceleration *= m_speed;

		//		�����x��ݒ肷��
		m_player->GetInformation()->SetAcceleration(m_acceleration);

		//		���x����ɒB���Ă��邩���f����
		m_player->GetCommonProcessing()->SpeedUpperLimit();

		//		���W�ɐݒ肷��
		m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
			m_player->GetInformation()->GetAcceleration() *
			LibrarySingleton::GetInstance()->GetElpsedTime());
	}
}

void PlayerSliding::ChangeStateJudgement()
{
	DirectX::Keyboard::State keyState =
		LibrarySingleton::GetInstance()->
		GetKeyboardStateTracker()->GetLastState();

	//		���C���[���Ԃ��Ƃ��ł��邩�ǂ���
	m_player->GetCommonProcessing()->WireActionJudgement();

	if (m_player->GetInformation()->GetAcceleration().Length() <= 10.0f)
	{
		//		��Ԃ�J�ڂ���(���Ⴊ�ݏ��)
		m_player->ChangeState(m_player->PlayerState::Crouching);
	}

	//		�S�[�������Ă��邩�ǂ���
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		��Ԃ�؂�ւ���i�S�[���j
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	//		Lcontrol�𗣂����ꍇ
	if (keyState.IsKeyUp(DirectX::Keyboard::LeftControl))
	{
		//		��Ԃ�J�ڂ���(�ړ����)
		m_player->ChangeState(m_player->PlayerState::Walk);
	}

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		space�ŃW�����v
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space))
	{
		//		��Ԃ�؂�ւ���(���Ⴊ��)
		m_player->ChangeState(m_player->PlayerState::Jump);
	}
}

void PlayerSliding::SlopeJudgement()
{
	//		�������Ă��鏰�̖@�������邩�ǂ���
	if (m_player->GetCollitionInformation()->GetFloorMeshHitNormalize().size() != 1)
	{
		m_slopeJudgement = false;

		return;
	}

	//		������̃x�N�g���Ə��̖@���̓��ς����
	float dot = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).
		Dot(m_player->GetCollitionInformation()->GetFloorMeshHitNormalize()[0]);

	//		��Ɣ��肷��p�x���ǂ������f����
	if (dot >= 1.0f || dot < 0.2f)
	{
		m_slopeJudgement = false;

		return;
	}

	//		�ړ��������󂯎��
	DirectX::SimpleMath::Vector2 acc2 = { 
		m_player->GetInformation()->GetAcceleration().x,
		m_player->GetInformation()->GetAcceleration().z };

	//		��̕������v�Z����
	DirectX::SimpleMath::Vector3 downhill = m_player->GetCollitionInformation()->GetFloorMeshHitNormalize()[0]
											- DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

	//		���������񎟌��ɂ���
	m_slidingVelocity = { downhill.x, downhill.z };

	//		���K��
	m_slidingVelocity.Normalize();

	//		���ς�
	if (m_slidingVelocity.Dot(acc2) > 0.8f)
	{
		//		���菈��
		m_slopeJudgement = true;

		m_accelerationTime = 1.0f;

		return;
	}

	m_slopeJudgement = false;
}
