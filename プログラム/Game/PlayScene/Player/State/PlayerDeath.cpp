/*
* @file		PlayerDeath.cpp
* @brief	�v���C���[�̎��S���
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "PlayerDeath.h"

#include "../Player.h"

PlayerDeath::PlayerDeath(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f),
	m_slowTime(0.0f),
	m_firstGravity(0.0f)
{
}

PlayerDeath::~PlayerDeath()
{
}

void PlayerDeath::Initialize()
{
	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		�����x���󂯎��
	m_firstAcceleration = m_player->GetInformation()->GetAcceleration();

	//		�d�͂��󂯎��
	m_firstGravity = m_player->GetInformation()->GetGravity();

	//		���S��Ԃɂ���
	m_player->GetGameManager()->TrueFlag(GameManager::DeathJudgement);

	//		���S�񐔂𑝂₷
	m_player->GetGameManager()->SetDeathCount(m_player->GetGameManager()->GetDeathCount() + 1);

	//		�A�j���[�V�����W�����v���
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Death);
}

void PlayerDeath::Update()
{
	//		����
	Deceleration();
}

void PlayerDeath::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		������
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,
		m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerDeath::Animation()
{
	//		�ҋ@�A�j���[�V����
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerDeath::Render()
{
}

void PlayerDeath::Finalize()
{
	m_time = 0.0f;

	m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3::Zero);

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		�v���C���[�̍��W�����Z�b�g����
	m_player->GetInformation()->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_player->GetInformation()->SetPlanPosition({ 0.0f, 0.0f, 0.0f });

	//		������
	m_player->GetInformation()->SetPlayerHeight({m_player->GetInformation()->GetPosition().x,
												 m_player->GetInformation()->GetPosition().y + 7.0f,
												 m_player->GetInformation()->GetPosition().z});
	m_player->GetInformation()->SetGravity(0.0f);
	m_player->GetInformation()->SetFallTime(0.0f);

	//		���S��Ԃ���������
	m_player->GetGameManager()->FalseFlag(GameManager::DamageObjectHit);
	m_player->GetGameManager()->FalseFlag(GameManager::FallDead);
	//		�Q�[���̑��x�����ɖ߂�
	m_player->GetGameManager()->SetGameSpeed(1.0f);
}

void PlayerDeath::Deceleration()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_time >= 1.0f) return;

	m_slowTime = 1.0f - pow(1 - m_time, 4.0f);

	DirectX::SimpleMath::Vector3 acceleration = DirectX::SimpleMath::Vector3::Lerp
	(m_firstAcceleration, DirectX::SimpleMath::Vector3::Zero, m_slowTime);

	m_player->GetInformation()->SetAcceleration(acceleration);

	//		���x�ƈړ��ʂ��v�Z����
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration()
		* LibrarySingleton::GetInstance()->GetElpsedTime());

	float gravity = Library::Lerp(m_firstGravity, 0.0f, m_slowTime);

	DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPlanPosition();

	position.y -= gravity * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_player->GetInformation()->SetPlanPosition(position);

	//		�Q�[���̑��x��x������
	m_player->GetGameManager()->SetGameSpeed(Library::Lerp(1.0f, 0.1f, m_slowTime));
}

void PlayerDeath::ChangeStateJudgement()
{
	//		���S��Ԃ���������Ώꍇ
	if (!m_player->GetGameManager()->FlagJudgement(GameManager::DeathJudgement))
	{
		//		������Ԃɂ���
		m_player->ChangeState(m_player->PlayerState::Start);
	}
}
