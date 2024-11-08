/*
* @file		CommonEnemyBulletManager.h
* @brief	��ʓI�ȓG�̒e�̃}�l�[�W���[
* @author	Morita
* @date		2024/05/06
*/

#pragma once

#include "CommonEnemyBullet.h"

class CommonEnemyBulletManager
{
public:

	//		�R���X�g���N�^
	CommonEnemyBulletManager();

	//		�f�X�g���N�^
	~CommonEnemyBulletManager();

	/*
	*	�G�l�~�[�̐�
	* 
	*	@param	(enemyCount)	�G�l�~�[�̐�
	*/
	void Initialize(int enemyCount);

	/*
	*	�X�V����
	*	
	*	@param	(timeSpeed)	���Ԃ̑��x
	*/
	void Update(float timeSpeed);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	//		�e
	std::vector<std::unique_ptr<CommonEnemyBullet>> m_bullet;

	//		�e�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_bulletPosition;

public:

	/*
	*	�e�̔���
	*	
	*	@param	(position)	���ˍ��W
	*	@param	(velocity)	���˕���
	*/
	void Firing(const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& velocity);

	/*
	*	�e�̍��W���󂯎��
	* 
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetBulletPosition() { return m_bulletPosition; }

};