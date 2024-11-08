/*
* @file		RespawnManager.h
* @brief	���X�|�[���}�l�[�W���[�̏���
* @author	Morita
* @date		2024/10/03
*/

#pragma once

#include "../GameManager/GameManager.h"

#include "RespawnPointRead.h"

class RespawnManager
{
public:
	//		�R���X�g���N�^
	RespawnManager(GameManager* gameManager);

	//		�f�X�g���N�^
	~RespawnManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update(DirectX::SimpleMath::Vector3 playerPosition);

	/*
	*	�����蔻��
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*	@param	(index)				�v�f��
	*/
	void CollitionProcess(DirectX::SimpleMath::Vector3 playerPosition,
						  int index);

	//		�f�o�b�N�`��
	void DebugRender();

	//		�I������
	void Finalize();

private:

	//		���X�|�[���̗v�f��
	int m_respownIndex;

	//		�Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	GameManager* m_gameManager;

	//		���X�|�[�����W
	DirectX::SimpleMath::Vector3 m_respawnPosition;

	//		���X�|�[�����W�ǂݍ���
	std::unique_ptr<RespawnPointRead> m_respawnPointRead;

	//		���X�|�[���͈̔̓��f��
	std::unique_ptr<DirectX::Model> m_respownRengeModel;

	//		�f�o�b�N�p�̃��[���h���W
	DirectX::SimpleMath::Matrix m_respownRengeWorld;

	//		����
	float m_direction;

public:

	/*
	*	���X�|�[�����W���󂯎��
	* 
	*	@return ���W
	*/
	DirectX::SimpleMath::Vector3 GetRespownPosition() { return m_respawnPosition; }
	
	/*
	*	���X�|�[���������󂯎��
	* 
	*	@return �p�x
	*/
	float GetRespownDirection() { return m_direction; }
};
