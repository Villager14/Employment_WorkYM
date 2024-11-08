/*
* @file		MeshCollitionManaager.cpp
* @brief	���b�V���̓����蔻��}�l�[�W���[
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "MeshCollitionManager.h"

MeshCollitionManager::MeshCollitionManager(GameManager* gameManager)
	:
	m_gameManager(gameManager)
{
	//		���b�V�����̓����蔻��̐���
	m_meshCollitionFloor = std::make_unique<MeshCollitionFloor>(this);

	//		���b�V���̕ǂ̓����蔻��
	m_meshCollitionWall = std::make_unique<MeshCollitionWall>(this);

	//		���b�V���̓��̓����蔻��
	m_meshCollitionHead = std::make_unique<MeshCollitionHead>(this);

	//		���b�V���̋��ʏ����̐���
	m_commonProcessing = std::make_unique<MeshCommonProcessing>();

}

MeshCollitionManager::~MeshCollitionManager()
{
}

void MeshCollitionManager::Initialize()
{
}

void MeshCollitionManager::MeshCollition(ObjectMesh* objectMesh,
			const DirectX::SimpleMath::Vector3& playerPosition,
			float height, bool slidingJudgement,
			GameManager* gameManager)
{
	//		�X���C�f�B���O��Ԃ��ǂ���
	if (slidingJudgement)
	{
		playerUnderRayLength = 1.0f;
	}
	else
	{
		playerUnderRayLength = 0.3f;
	}

	//		���C�̒�����ݒ肷��
	m_meshCollitionFloor->SetRayLength(playerUnderRayLength, PLAYER_ABOVE_RAY_LENGTH);

	//		�ǂ̓����蔻��
	m_wallHit = m_meshCollitionWall->WallCollition(objectMesh, playerPosition, height);

	//		�I�u�W�F�N�g�^�C�v���ǂ̎�
	if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Wall)
	{
		//		�ǂɓ��������@��
		m_wallHitNormalize = m_meshCollitionWall->GetNormalize();
	}

	//		���̓����蔻��
	m_meshCollitionHead->HeadCollition(objectMesh, playerPosition, height);

	//		�I�u�W�F�N�g�^�C�v���S�[���̎�
	if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Goal &&
		m_wallHit.size() != 0)
	{
		//		�S�[����ݒ肷��
		//gameManager->SetGoalJudgement(true);
		gameManager->TrueFlag(GameManager::GoalJudgement);
	}

	m_wallWalkPlayerPosition = m_meshCollitionWall->WallWalk(objectMesh, playerPosition);

	if (m_wallHit.size() == 0)
	{
		m_playerPosition = playerPosition;
	}
	else
	{
		m_playerPosition = { m_wallHit[0].x, playerPosition.y, m_wallHit[0].y };
	}

	//		���̓����蔻����X�V����
	m_meshHitPoint = m_meshCollitionFloor->FloorCollition(objectMesh, m_playerPosition);

	if (m_meshHitPoint.size() != 0)
	{
		//		�S�[���ɓ������Ă���ꍇ
		if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Goal)
		{
			//		�S�[����ݒ肷��
			gameManager->TrueFlag(GameManager::GoalJudgement);
		}
	}

	//		�_���[�W�I�u�W�F�N�g���ǂ���
	if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::DamageObject)
	{
		DamageHitJudgement();
	}
}

void MeshCollitionManager::MeshHitPointClear()
{
	m_meshHitPoint.clear();
	//		�ǂ̓����蔻���
	m_wallHit.clear();
	m_wallWalkPlayerPosition.clear();
	m_wallHitNormalize.clear();
	m_meshHitPoint.clear();
}

void MeshCollitionManager::DamageHitJudgement()
{
	//		�_���[�W�I�u�W�F�N�g�ɓ��������ꍇ
	if (m_meshHitPoint.size()	!= 0 ||
		m_wallHit.size()		!= 0 ||
		m_meshCollitionHead->GetHitJudgement())
	{
		//		���S��Ԃɂ���
		m_gameManager->TrueFlag(GameManager::DamageObjectHit);
	}
}

void MeshCollitionManager::Finalize()
{
	m_meshHitPoint.clear();
	//		�ǂ̓����蔻���
	m_wallHit.clear();
	m_wallWalkPlayerPosition.clear();
	m_wallHitNormalize.clear();
	m_meshHitPoint.clear();

	m_meshCollitionFloor->Finalize();
	m_meshCollitionWall->Finalize();
}
