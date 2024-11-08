/*
* @file		MeshCollitionManager.h
* @brief	���b�V���̓����蔻��}�l�[�W���[
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Triangle.h"

#include "ObjectMesh.h"

#include "MeshCollitionFloor.h"

#include "MeshCollitionWall.h"

#include "MeshCollitionHead.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "MeshCommonProcessing.h"

class MeshCollitionManager
{
public:
	//		�R���X�g���N�^
	MeshCollitionManager(GameManager* gameManager);

	//		�f�X�g���N�^
	~MeshCollitionManager();

	//		����������
	void Initialize();

	/*
	*	���b�V���̓����蔻��
	*
	*	@param	(objctMesh)			�I�u�W�F�N�g���b�V��
	*	@param	(playerPosition)	�v���C���[�̍��W
	*	@param	(height)			����
	*	@param	(slidingJudgement)	�X���C�f�B���O�����Ă��邩�ǂ���
	*	@param	(gameObject)		�Q�[���}�l�[�W���[
	*/
	void MeshCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		float height, bool slidingJudgement, GameManager* gameManager);


	void MeshHitPointClear();

	//		�_���[�W�I�u�W�F�N�g�ɓ����������ǂ���?
	void DamageHitJudgement();

	//		�I������
	void Finalize();

private:

	//		�v���C���[�̃��C�̒�����
	const float PLAYER_ABOVE_RAY_LENGTH = 2.0f;

private:

	float playerUnderRayLength = 0.5f;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		���b�V���̓��������|�C���g
	std::vector<DirectX::SimpleMath::Vector3> m_meshHitPoint;

	//		�ǂ̓����蔻��
	std::vector<DirectX::SimpleMath::Vector2> m_wallHit;

	//		�ǂ̖@���̓����蔻��
	std::vector<DirectX::SimpleMath::Vector3> m_wallHitNormalize;

	//		���b�V�����̓����蔻��
	std::unique_ptr<MeshCollitionFloor> m_meshCollitionFloor;

	//		���b�V���̕Ǔ����蔻��
	std::unique_ptr<MeshCollitionWall> m_meshCollitionWall;

	//		���b�V���̓��̓����蔻��
	std::unique_ptr<MeshCollitionHead> m_meshCollitionHead;

	//		�Ǖ����@��
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		�Ǖ������̃v���C���[�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wallWalkPlayerPosition;

	//		���b�V���̋��ʏ���
	std::unique_ptr<MeshCommonProcessing> m_commonProcessing;

	//		�Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	GameManager* m_gameManager;
public:

	/*
	*	���b�V���̓��������|�C���g���󂯎��
	*
	*	@return		���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetMeshHitPoint() { return m_meshHitPoint; }

	/*
	*	���b�V�����ǂɓ��������|�C���g���󂯎��
	*
	*	@return		�ړ���
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetMeshWallHit() { return m_wallHit; }

	/*
	*	���b�V���ǂɓ����������̖@�����󂯎��
	*
	*	@return �@��
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallHitNormalize() { return m_wallHitNormalize; }

	/*
	*	�ǂ̕����@����ݒ肷��
	*
	*	@param	(normalize) �@��
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	�ǂ̕����@�����󂯎��
	*
	*	@return �@��
	*/
	const DirectX::SimpleMath::Vector3& GetWallWalkNormalize() { return m_wallWalkNormalize; }

	/*
	*	�Ǖ������̃v���C���[�̍��W���󂯎��
	*
	*	@return �Ǖ������̃v���C���[�̍��W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallWalkPlayerPosition() { return m_wallWalkPlayerPosition; }

	/*
	*	���̖@�����󂯎��
	*
	*	@return �@��
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetFloorNormalize() { return m_meshCollitionFloor->GetNormalize(); }

	/*
	*	�ߋ��̃v���C���[�̍��W��ݒ肷��
	* 
	*	@param	(playerPosition)	�v���C���[���W
	*/
	void SetPastPlayerPosition(DirectX::SimpleMath::Vector3 playerPosition) {
		m_meshCollitionFloor->SetPastPlayerPosition(playerPosition);
		m_meshCollitionWall->SetPastPosition(playerPosition);
	}

	/*
	*	���b�V���̋��ʏ������󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MeshCommonProcessing* GetCommon() { return m_commonProcessing.get(); }

	/*
	*	���ɓV�䂪�����������ǂ����H
	*	
	*	@return true : �������Ă��� fales : �������Ă��Ȃ�
	*/
	const bool GetHeadHitJudgement() { return m_meshCollitionHead->GetHitJudgement(); }
};