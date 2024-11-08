/*
* @file		EnemyManager.cpp
* @brief	�G�l�~�[�}�l�[�W���[
* @author	Morita
* @date		2024/04/29
*/

#include "pch.h"

#include "EnemyManager.h"

#include "Enemy/EnemyInformation.h"

EnemyManager::EnemyManager()
{
	//		�G�l�~�[�̏��̓ǂݍ��݂̐���
	m_enemyInformation = std::make_unique<LoadingEnemyInformation>();
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Initialize()
{
	m_enemyInformation->Load(1);

	/*
	for (int i = 0, max = static_cast<int>(m_enemyInformation->GetInformation()->size());
		i < max; ++i)
	{
		if ((*m_enemyInformation->GetInformation())[i].enemyType
			 == EnemyInformation::NormalEnemy)
		{
			//		��ʃG�l�~�[�̐���
			m_commonEnemy.push_back(std::make_unique<CommonEnemy>
				((*m_enemyInformation->GetInformation())[i]));

			m_commonEnemy[i]->Initialize();
		}
	}
	*/
	//		��ʃG�l�~�[�̒e�̃}�l�[�W���[�̐���
	m_commonEnemyBulletManager = std::make_unique<CommonEnemyBulletManager>();

	//		��ʃG�l�~�[�e�̃}�l�[�W���[�̏�����
	m_commonEnemyBulletManager->Initialize(static_cast<int>(m_commonEnemy.size()));
}

void EnemyManager::Update(const float& timeSpeed,
	const DirectX::SimpleMath::Vector3& playerPosition)
{
	for (int i = 0, max = static_cast<int>(m_commonEnemy.size()); i < max; ++i)
	{
		//		�X�V����
		m_commonEnemy[i]->Update(playerPosition, timeSpeed);

		//		�U����Ԃ��ǂ���
		if (m_commonEnemy[i]->GetInformation()->GetAttackJudgement())
		{
			m_commonEnemyBulletManager->Firing(m_commonEnemy[i]->GetAttackPosition(),
				m_commonEnemy[i]->GetInformation()->GetAttackDirection());

			//		�U����Ԃ��I������
			m_commonEnemy[i]->GetInformation()->SetAttackJudgement(false);
		}
	}

	//		�e�Ǘ��N���X�̍X�V
	m_commonEnemyBulletManager->Update(timeSpeed);
}

void EnemyManager::Render()
{
	for (int i = 0, max = static_cast<int>(m_commonEnemy.size()); i < max; ++i)
	//		�`�揈��
	m_commonEnemy[i]->Render();

	//		�e�Ǘ��N���X�̕`��
	m_commonEnemyBulletManager->Render();
}
