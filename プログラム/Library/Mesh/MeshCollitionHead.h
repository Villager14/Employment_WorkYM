/*
* @file		MeshCollitionHead.h
* @brief	���b�V���̓����蔻�蓪
* @author	Morita
* @date		2024/07/22
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionManager;

class MeshCollitionHead
{
public:

	//		�R���X�g���N�^
	MeshCollitionHead(MeshCollitionManager* meshCollitionManager);

	//		�f�X�g���N�^
	~MeshCollitionHead();

	void HeadCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		const float playerHeight);

	//		�V�䂩�ǂ���
	bool CeilingJudgement(const DirectX::SimpleMath::Vector3& normalize);

	/*
	*	�I�u�W�F�N�g�̓����蔻��
	*
	*	@param	(objectMesh)	�I�u�W�F�N�g���b�V��
	*	@param	(index)			�v�f
	*/
	void ObjectCollider(ObjectMesh* objectMesh, int index);

	/*
	*	���̏���������
	*
	*	@param	(playerPosition)	�v���C���[�̍��W
	*	@param	(playerHeight)		�v���C���[�̍���
	*/
	void HeightCollitionInitalize(const DirectX::SimpleMath::Vector3& playerPosition,
								 const float playerHeight);

private:

	MeshCollitionManager* m_meshCollitionManager;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		���C�̃X�^�[�g���W
	DirectX::SimpleMath::Vector3 m_rayStart;

	//		���C�̏I�����W
	DirectX::SimpleMath::Vector3 m_rayEnd;

	//		�������Ă���|�C���g
	DirectX::SimpleMath::Vector3 m_hitPoint;

	//		�������Ă��邩�ǂ���
	bool m_hitJudgement;

public:

	bool GetHitJudgement() { return m_hitJudgement; }
};