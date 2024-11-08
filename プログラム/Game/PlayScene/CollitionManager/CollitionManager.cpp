/*
* @file		CollitionManager.cpp
* @brief	�����蔻��}�l�[�W���[
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "CollitionManager.h"

CollitionManager::CollitionManager(GameManager* gameManager)
	:
	m_gameManager(gameManager)
{
	//		���b�V���̓����蔻��̐���
	m_meshCollition = std::make_unique<MeshCollitionManager>(gameManager);

	//		�����蔻��̏��
	m_collitionInformation = std::make_unique<CollitionInformation>();
}

CollitionManager::~CollitionManager()
{
}

void CollitionManager::Initialize()
{
	//		������������
	//m_meshCollition->Initialize();

	//		�e�̓����蔻��̐���
	//m_bulletCollition = std::make_unique<BulletCollition>();

}

void CollitionManager::Update(PlayerInformationCollition* playerInformationCollition)
{
	//		�����蔻��̏�����
	m_meshCollition->MeshHitPointClear();

	//		�@���𑗂�
	m_meshCollition->SetWallWalkNormalize(playerInformationCollition->GetWallWalkNormalize());

	//		�v���C���[�̍��������߂�
	float height = playerInformationCollition->GetPlayerHeight().y - playerInformationCollition->GetPlayerPosition().y;

	//		�v���C���[�̍��W���󂯎��
	m_playerPosition = playerInformationCollition->GetPlayerPosition();

	//		�ȑO�̓����蔻����폜����
	m_collitionInformation->Clear();

	//		�ÓI�ȓ����蔻��
	for (int i = 0; i < m_objectMesh.size(); ++i)
	{
		if (m_objectMesh[i]->GetStaticObjectJudgement())
		{
			CollitionProcess(playerInformationCollition, height, i);

			/*
			//		���b�V���̓����蔻��
			m_meshCollition->MeshCollition(m_objectMesh[i], m_playerPosition, height, 
								playerInformationCollition->GetSlidingJudgement(), m_gameManager);

			//		���̓����蔻��̏���ݒ肷��
			m_collitionInformation->FloorMeshInformation(m_meshCollition->GetMeshHitPoint(),
				m_meshCollition->GetFloorNormalize(), m_playerPosition);

			//		�V��ɓ������Ă���ꍇ
			if (m_meshCollition->GetHeadHitJudgement())
			{
				//		�������Ă���
				m_collitionInformation->SetCeilingJudgement(true);
			}

			//		�ǂ̓����蔻�����ݒ肷��
			m_playerPosition = m_collitionInformation->WallMeshInformation(
					m_meshCollition->GetMeshWallHit(),
					m_meshCollition->GetWallHitNormalize(),
					m_meshCollition->GetWallWalkPlayerPosition(),
					m_playerPosition);
			*/
		}
	}

	if (m_collitionInformation->GetFloorMeshHitPoint().size() > 0)
	{
		m_playerPosition = m_collitionInformation->GetFloorMeshHitPoint()[0];

		m_meshCollition->SetPastPlayerPosition(m_playerPosition);
	}
	else
	{
		m_meshCollition->SetPastPlayerPosition(m_playerPosition);
	}

	//		�e�̓����蔻��
	//m_bulletCollition->Collition(playerInformationCollition->GetPlayerPosition(), playerInformationCollition->GetPlayerHeight(), m_bulletPosition);
}

void CollitionManager::CollitionProcess(
	PlayerInformationCollition* playerInformationCollition, float height,
	int index)
{
	//		���b�V���̓����蔻��
	m_meshCollition->MeshCollition(m_objectMesh[index], m_playerPosition, height,
		playerInformationCollition->GetSlidingJudgement(), m_gameManager);

	//		���̓����蔻��̏���ݒ肷��
	m_collitionInformation->FloorMeshInformation(m_meshCollition->GetMeshHitPoint(),
		m_meshCollition->GetFloorNormalize(), m_playerPosition);

	//		�V��ɓ������Ă���ꍇ
	if (m_meshCollition->GetHeadHitJudgement())
	{
		//		�������Ă���
		m_collitionInformation->SetCeilingJudgement(true);
	}

	//		�ǂ̓����蔻�����ݒ肷��
	m_playerPosition = m_collitionInformation->WallMeshInformation(
		m_meshCollition->GetMeshWallHit(),
		m_meshCollition->GetWallHitNormalize(),
		m_meshCollition->GetWallWalkPlayerPosition(),
		m_playerPosition);
}

void CollitionManager::Finalize()
{
	m_meshCollition->Finalize();
	m_collitionInformation->Finalize();
}
