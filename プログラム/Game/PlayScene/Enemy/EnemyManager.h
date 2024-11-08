/*
* @file		EnemyManager.h
* @brief	�G�l�~�[�}�l�[�W���[
* @author	Morita
* @date		2024/04/29
*/

#pragma once

#include "Enemy/CommonEnemy/CommonEnemy.h"

#include "Enemy/CommonEnemy/CommonEnemyBulletManager.h"

#include "Enemy/LoadingEnemyInformation.h"

class EnemyManager
{
public:

	//		�R���X�g���N�^
	EnemyManager();

	//		�f�X�g���N�^
	~EnemyManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(timeSPeed)			���Ԃ̑��x
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update(const float& timeSpeed,
		const DirectX::SimpleMath::Vector3& playerPosition);

	//		�`�揈��
	void Render();
private:

	//		��ʃG�l�~�[
	std::vector<std::unique_ptr<CommonEnemy>> m_commonEnemy;

	//		��ʃG�l�~�[�̒e�̃}�l�[�W���[
	std::unique_ptr<CommonEnemyBulletManager> m_commonEnemyBulletManager;

	//		�G�l�~�[�̏��̓ǂݍ���
	std::unique_ptr<LoadingEnemyInformation> m_enemyInformation;

public:

	/*
	*	�e�̍��W���󂯎��
	* 
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetBulletPosition()
				{ return m_commonEnemyBulletManager->GetBulletPosition(); }
};