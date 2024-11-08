/*
* @file		CommonEnemyBulletManager.h
* @brief	��ʓI�ȓG�̒e�̃}�l�[�W���[
* @author	Morita
* @date		2024/05/06
*/

#include "pch.h"

#include "CommonEnemyBulletManager.h"


CommonEnemyBulletManager::CommonEnemyBulletManager()
{
}

CommonEnemyBulletManager::~CommonEnemyBulletManager()
{
}

void CommonEnemyBulletManager::Initialize(int enemyCount)
{
	//		�G�l�~�[�̐��~�R�̋ʂ𐶐�����
	for (int i = 0; i < 3 * enemyCount; ++i)
	{
		//		�e�̒ǉ�
		m_bullet.push_back(std::make_unique<CommonEnemyBullet>());

		//		����������
		m_bullet[i]->Initialize();
	}
}

void CommonEnemyBulletManager::Update(float timeSpeed)
{
	//		���
	m_bulletPosition.clear();

	for (int i = 0, max = static_cast<int>(m_bullet.size()); i < max; ++i)
	{
		//		���˂��Ă��邩�ǂ���
		if (!m_bullet[i]->GetFiringJudgement()) continue;
		
		//		�X�V����
		m_bullet[i]->Update(timeSpeed);

		//		�e�̍��W��ݒ肷��
		m_bulletPosition.push_back(m_bullet[i]->GetPosition());
	}
}

void CommonEnemyBulletManager::Render()
{
	for (int i = 0, max = static_cast<int>(m_bullet.size()); i < max; ++i)
	{
		//		���˂��Ă��邩�ǂ���
		if (!m_bullet[i]->GetFiringJudgement()) continue;

		//		�X�V����
		m_bullet[i]->Render();
	}
}

void CommonEnemyBulletManager::Finalize()
{
}

void CommonEnemyBulletManager::Firing(const DirectX::SimpleMath::Vector3& position,
									  const DirectX::SimpleMath::Vector3& velocity)
{
	for (int i = 0, max = static_cast<int>(m_bullet.size()); i < max; ++i)
	{
		//		���˂��Ă��邩�ǂ���
		if (m_bullet[i]->GetFiringJudgement()) continue;

		//		���ˏ�Ԃɂ���
		m_bullet[i]->SetFiringJudgement(true);

		//		�e�̏���ݒ肷��
		m_bullet[i]->SetBulletInformation(position, velocity);
	}
}
