/*
* @file		CollitionManager.h
* @brief	�����蔻��}�l�[�W���[
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Library/Mesh/MeshCollitionManager.h"

#include "Library/Mesh/ObjectMesh.h"

#include "BulletCollition.h"

#include "CollitionInformation.h"

#include "Game/PlayScene/Player/PlayerInformationCollition.h"

#include "Game/PlayScene/GameManager/GameManager.h"

class CollitionManager
{
public:

	//		�R���X�g���N�^
	CollitionManager(GameManager* gameManager);

	//		�f�X�g���N�^
	~CollitionManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(playerInformationCollition)	�C���X�^���X�̃|�C���^
	*/
	void Update(PlayerInformationCollition* playerInformationCollition);

	void CollitionProcess(PlayerInformationCollition* playerInformationCollition,
		float height, int index);

	//		�I������
	void Finalize();

private:

	//		���b�V���̓����蔻��
	std::unique_ptr<MeshCollitionManager> m_meshCollition;

	//		�I�u�W�F�N�g���b�V��
	std::vector<ObjectMesh*> m_objectMesh;
	
	//		�e�̓����蔻��
	std::unique_ptr<BulletCollition> m_bulletCollition;

	//		�Ǖ����@��
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		�e�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_bulletPosition;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		�����蔻��̏��
	std::unique_ptr<CollitionInformation> m_collitionInformation;

	//		�Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	GameManager* m_gameManager;

public:

	/*
	*	�����蔻��̏����󂯎��	
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	CollitionInformation* GetCollitionInformation() { return m_collitionInformation.get(); }

	/*
	*	���b�V���̏����󂯎��
	* 
	*	@param	(objectMesh)	���b�V���̃C���X�^���X�̃|�C���^
	*/
	void SetObjectMesh(std::vector<ObjectMesh*> objectMesh) { m_objectMesh = objectMesh; }

	/*
	*	�ǂ̕����@����ݒ肷��
	* 
	*	@param	(normalize) �@��
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	�e�̍��W��ݒ肷��
	* 
	*	@param	(position)	���W
	*/
	void SetBulletPoistion(std::vector<DirectX::SimpleMath::Vector3> position) { m_bulletPosition = position; }
};