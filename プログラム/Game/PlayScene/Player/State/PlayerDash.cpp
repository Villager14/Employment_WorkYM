/*
* @file		PlayerDash.cpp
* @brief	�v���C���[�̃_�b�V��
* @author	Morita
* @date		2024/04/29
*/

#include "pch.h"

#include "PlayerDash.h"

#include "../Player.h"

PlayerDash::PlayerDash(Player* player)
	:
	m_player(player),
	m_acceraration(0.0f),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_deceleration(0.0f),
	m_firstSpeed(0.0f)
{
}

PlayerDash::~PlayerDash()
{
}

void PlayerDash::Initialize()
{
	//		�����x�N�g��
	m_direction = m_player->GetCameraInformation()->GetViewVelocity();

	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		��������
	m_player->GetInformation()->SetFallTime(0.0f);

	//		�_�b�V�����ł��Ȃ���Ԃɂ���
	m_player->GetInformation()->SetDashJudgement(false);

	//		�����̑��x
	m_firstSpeed = m_player->GetInformation()->GetAcceleration().Length();

	//		�J�������~������
	m_player->GetInformation()->SetCameraStop(true);

	//		����h�炳�Ȃ���Ԃɂ���
	m_player->GetInformation()->SetHeadShakingJudgement(false);

	//		�A�j���[�V�����������
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Dash);

	//		�_�b�V�����ʉ����ʉ��̍Đ�
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::Dash);

	//		�Q�[���}�l�[�W���[�̃_�b�V���t���O��ON�ɂ���
	m_player->GetGameManager()->TrueFlag(GameManager::DashJudgement);
}

void PlayerDash::Update()
{
	//		�ړ�����
	MoveProcessing();

	//		�d�͏���
	m_player->GetCommonProcessing()->Gravity();
}

void PlayerDash::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		������
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerDash::Animation()
{
	//		�_�b�V���̃A�j���[�V����
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerDash::Render()
{
}

void PlayerDash::Finalize()
{
	m_acceraration = 0.0f;

	m_deceleration = 0.0f;

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	//--
	//		�ŏ��̑��x�ɖ߂�
	//--
	
	//		�����x���󂯎��
	DirectX::SimpleMath::Vector3 velocity = m_player->GetInformation()->GetAcceleration();

	//		���K��
	velocity.Normalize();

	//		�����x��ݒ肷��i���x���ŏ��̑��x�ɂ���j
	m_player->GetInformation()->SetAcceleration(velocity * m_firstSpeed);

	//		�J�������~���I������
	m_player->GetInformation()->SetCameraStop(false);

	//		�Q�[���}�l�[�W���[�̃_�b�V���t���O��OFF�ɂ���
	m_player->GetGameManager()->FalseFlag(GameManager::DashJudgement);
}

void PlayerDash::MoveProcessing()
{
	if (m_acceraration < 1.0f) Acceratation();
	else Deceleration();
}

void PlayerDash::Acceratation()
{
	m_acceraration += LibrarySingleton::GetInstance()->GetElpsedTime()
		* 8.0f;

	float move = m_acceraration;

	//		�������x����Lerp���g���������Ă���
	float speed = Library::Lerp(m_firstSpeed, DASH_MAX_SPEED, move);

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		(m_direction * speed) *
		LibrarySingleton::GetInstance()->GetElpsedTime());

	//		�����x�̐ݒ�
	m_player->GetInformation()->SetAcceleration(m_direction * speed);
}

void PlayerDash::Deceleration()
{
	//		�o�ߎ���
	m_deceleration += LibrarySingleton::GetInstance()->GetElpsedTime()
		* 3.0f;

	//		��ȏ�ɂȂ�Ȃ��悤�ɂ���
	m_deceleration = Library::Clamp(m_deceleration, 0.0f, 1.0f);

	//		�C�[�W���O�֐�(easeInExpo)
	float move = 0.0f;

	if (m_deceleration != 0)
	{
		move = pow(2.0f, 10.0f * m_deceleration - 10.0f);
	}

	//		�������x����Lerp���g���������Ă���
	float speed = Library::Lerp(DASH_MAX_SPEED, m_firstSpeed, move);

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		(m_direction * speed) *
		LibrarySingleton::GetInstance()->GetElpsedTime());

	//		�����x�̐ݒ�
	m_player->GetInformation()->SetAcceleration(m_direction * speed);
}

void PlayerDash::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		�Ǖ�����Ԃ��ǂ���
	m_player->GetCommonProcessing()->WallWalkJudgement();

	//		�S�[�������Ă��邩�ǂ���
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		��Ԃ�؂�ւ���i�S�[���j
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	if (m_deceleration >= 1.0f)
	{
		//		��Ԃ�J�ڂ���(����)
		m_player->ChangeState(m_player->PlayerState::Walk);
	}
}
