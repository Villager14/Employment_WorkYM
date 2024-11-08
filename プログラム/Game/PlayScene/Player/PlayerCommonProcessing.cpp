/*
* @file		PlayerCommonProcessing.cpp
* @brief	�v���C���[�̋��ʏ����N���X
* @author	Morita
* @date		2024/07/18
*/

#include "pch.h"

#include "PlayerCommonProcessing.h"

#include "Player.h"

#include <bitset>

PlayerCommonProcessing::PlayerCommonProcessing(Player* player)
	:
	m_player(player)
{
}

PlayerCommonProcessing::~PlayerCommonProcessing()
{
}

void PlayerCommonProcessing::Gravity(bool weekJudgement)
{
	float speed = 2.0f;

	//		�������Ԃ��󂯎��
	float fallTime = m_player->GetInformation()->GetFallTime();

	if (weekJudgement)
	{
		speed = 1.0f;

		//		�d�͉����x
		fallTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed;

		m_player->GetInformation()->SetGravity(m_player->GetInformation()->
			GetGravitationalAcceleration() * (fallTime * fallTime));

	}
	else
	{
		//		�d�͉����x
		fallTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed * 
			(m_player->GetInformation()->GetTimeSpeed() * m_player->GetInformation()->GetTimeSpeed());

		m_player->GetInformation()->SetGravity(m_player->GetInformation()->GetGravitationalAcceleration()
											* (fallTime * fallTime));
	}

	//		�������Ԃ�ݒ肷��
	m_player->GetInformation()->SetFallTime(fallTime);

	m_player->GetInformation()->SetPlanPosition({ m_player->GetInformation()->GetPlanPosition().x,
									 m_player->GetInformation()->GetPlanPosition().y - 
									m_player->GetInformation()->GetGravity() *
									LibrarySingleton::GetInstance()->GetElpsedTime()
									* m_player->GetInformation()->GetTimeSpeed(),
									 m_player->GetInformation()->GetPlanPosition().z });
}

bool PlayerCommonProcessing::FloorMeshHitJudgement()
{
	//		���ɓ������Ă��邩
	if (m_player->GetCollitionInformation()->GetFloorMeshHitPoint().size() != 0)
	{
		//		���b�V����Y���W���󂯎��
		m_player->GetInformation()->SetPlanPosition({ m_player->GetInformation()->GetPlanPosition().x,
			m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y,
			m_player->GetInformation()->GetPlanPosition().z });

		//		�������Ԃ��O�ɂ���
		m_player->GetInformation()->SetFallTime(0.0f);

		//		�W�����v�ł����Ԃɂ���
		m_player->GetInformation()->SetJumpJudgement(true);

		//		����h�炷��Ԃɂ���
		m_player->GetInformation()->SetHeadShakingJudgement(true);

		return true;
	}

	//		����h�炳�Ȃ���Ԃɂ���
	m_player->GetInformation()->SetHeadShakingJudgement(false);

	return false;
}

bool PlayerCommonProcessing::WallMeshHitJudgement()
{
	if (m_player->GetCollitionInformation()->GetWallHitVelocity().size() > 0)
	{
		DirectX::SimpleMath::Vector3 planePosition = m_player->GetInformation()->GetPlanPosition();

		planePosition.x = m_player->GetCollitionInformation()->GetWallHitVelocity()[0].x;
		planePosition.z = m_player->GetCollitionInformation()->GetWallHitVelocity()[0].y;

		m_player->GetInformation()->SetPlanPosition(planePosition);

		return true;
	}

	return false;
}

void PlayerCommonProcessing::PlayerHeightTransition(const float& firstHeight, const float& endHeight, const float& speed)
{
	DirectX::SimpleMath::Vector3 headPosition = m_player->GetInformation()->GetPosition();

	float heightTime = m_player->GetInformation()->GetHeightTime();

	//		��ȏ�Ȃ珈�������Ȃ�
	if (heightTime < 1.0f)
	{
		if (!m_player->GetCollitionInformation()->GetCeilingJudgement())
		{
			//		�J�ڑ��x
			heightTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed;
		}

		//		��ȏ�ɂȂ�Ȃ��悤�ɂ���
		heightTime = Library::Clamp(heightTime, 0.0f, 1.0f);

		//		easeOutQuart
		float move = 1.0f - pow(1.0f - heightTime, 4.0f);

		m_player->GetInformation()->SetHeightTime(heightTime);

		//		���[�v�ŏ����̍������痧���̍�����
		headPosition.y = m_player->GetInformation()->GetPosition().y + Library::Lerp(firstHeight, endHeight, move);
	}
	else
	{
		headPosition.y = m_player->GetInformation()->GetPosition().y + endHeight;
	}

	if (m_player->GetInformation()->GetHeadMove() > 0.0f)
	{

		float headMove = m_player->GetInformation()->GetHeadMove();

		//		�ړ����x
		headMove -= m_player->GetInformation()->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

		//		�ړ��ʂ̐���
		headMove = Library::Clamp(headMove, 0.0f, m_player->GetInformation()->GetHeadMoveMAX());

		

		//		���̈ړ��ʂ𑫂�
		headPosition.x += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().x * headMove;
		headPosition.z += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().z * headMove;

		m_player->GetInformation()->SetHeadMove(headMove);
	}

	//		������ݒ肷��
	m_player->GetInformation()->SetPlayerHeight(headPosition);

}

void PlayerCommonProcessing::SpeedUpperLimit()
{
	float speed = m_player->GetInformation()->GetAcceleration().Length();

	if (speed <= 70.0f) return;

	DirectX::SimpleMath::Vector3 velocity = m_player->GetInformation()->GetAcceleration();

	velocity.Normalize();

	m_player->GetInformation()->SetAcceleration(velocity * 70.0f);
}

DirectX::SimpleMath::Vector3 PlayerCommonProcessing::Direction(bool* keyPressjudgement)
{
	std::bitset<4> directionbit;

	//		�L�[�{�[�hState�̎擾
	DirectX::Keyboard::State m_keyboard = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		�ړ��������
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::W))
	{
		directionbit.set(0, 1);

		direction.z += 1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::S))
	{
		directionbit.set(1, 1);

		direction.z += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::D))
	{
		directionbit.set(2, 1);

		direction.x += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::A))
	{
		directionbit.set(3, 1);

		direction.x += 1.0f;
	}

	if (directionbit != 0)
	{
		//		�L�[��������Ă���
		*keyPressjudgement = true;
	}

	return direction;
}

DirectX::SimpleMath::Vector3 PlayerCommonProcessing::MoveDirection(const DirectX::SimpleMath::Vector3 direction)
{
	//		�J�����̌���
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x));

	//		�ړ��������
	return DirectX::SimpleMath::Vector3::Transform(
		direction, matrixY.Invert());
}

bool PlayerCommonProcessing::WireActionJudgement()
{
	//		���C���[���g�p�ł��Ȃ���Ԃɂ���
	m_player->GetInformation()->SetWireJudgement(false);

	//		���C���[�I�u�W�F�N�g���Ȃ��ꍇ
	if (m_player->GetWireObjectInformation()->size() == 0)
	{
		//		���������Ȃ�
		return false;
	}

	for (int i = 0, max = static_cast<int>((*m_player->GetWireObjectInformation()).size()); i < max; ++i)
	{

		if (!(*m_player->GetWireObjectInformation())[i].m_usedJudgement || (*m_player->GetWireObjectInformation())[i].m_actionJudgement) continue;

		//		���C���[�̂������
		DirectX::SimpleMath::Vector3 wireDirection = (*m_player->GetWireObjectInformation())[i].position - m_player->GetInformation()->GetPlayerHeight();

		//		�����x�N�g��
		DirectX::SimpleMath::Vector3 viewDirection = m_player->GetInformation()->GetViewVelocity();

		//		���K��
		wireDirection.Normalize();
		viewDirection.Normalize();

		//		���ς����
		float dot = wireDirection.Dot(viewDirection);

		//		���C���[�̕����������Ă��Ȃ�������
		if (dot < 0.9f) continue;

		//		���C���[���g�p�ł����Ԃɂ���
		m_player->GetInformation()->SetWireJudgement(true);

		//		�}�E�X�g���b�J�[�̒l���󂯎��
		DirectX::Mouse::ButtonStateTracker* mouse = LibrarySingleton::GetInstance()->GetButtonStateTracker();

		//		�}�E�X�������ꂽ�ꍇ
		if (mouse->leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			//		�ړ����C���[�̍��W��ݒ肷��
			DirectX::SimpleMath::Vector3 wireMovePosition = (*m_player->GetWireObjectInformation())[i].position;

			wireMovePosition.y -= 12.0f;

			//		�ړ����C���[���W��ݒ肷��
			m_player->GetInformation()->SetWireMovePosition(wireMovePosition);

			//m_player->ChangeState(Player::PlayerState::Wire);

			//(*m_player->GetWireObjectInformation()[i]).m_actionJudgement = true;

			m_player->ChangeWireState(i);

			return true;
		}
	}

	return false;
}

void PlayerCommonProcessing::WallWalkJudgement()
{
	//		�ǂɓ������Ă���ꍇ
	if (m_player->GetCollitionInformation()->GetMeshWallNormalize().size() == 1)
	{
		DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

		acceleation.Normalize();

		float dot = m_player->GetCollitionInformation()->GetMeshWallNormalize()[0].Dot(acceleation);

		//		�v���C���[�����̊p�x�������Ă���ꍇ����������
		if (dot <= -0.1f && dot >= -0.95f)
		{
			//		�@����������
			m_player->GetPlayerInformationCollition()->SetWallWalkNormalize(m_player->GetCollitionInformation()->GetMeshWallNormalize()[0]);

			//		��Ԃ�؂�ւ���(�Ǖ������)
			m_player->ChangeState(Player::PlayerState::WallWalk);

			return;
		}
	}
}

void PlayerCommonProcessing::DashCoolTime()
{
	if (!m_player->GetInformation()->GetDashJudgement())
	{
		//		�N�[���^�C��
		float coolTime = m_player->GetInformation()->GetDashCoolTime();

		//		�o�ߎ���
		coolTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		//		��莞�Ԃ�������
		if (coolTime >= 2.0f)
		{
			m_player->GetInformation()->SetDashJudgement(true);
			coolTime = 0.0f;
		}

		//		�N�[���^�C����ݒ肷��
		m_player->GetInformation()->SetDashCoolTime(coolTime);
	}
}
