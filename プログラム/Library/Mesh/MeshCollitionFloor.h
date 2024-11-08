/*
* @file		MeshCollitionFloor.h
* @brief	���b�V���̓����蔻�菰
* @author	Morita
* @date		2024/04/27
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionManager;

class MeshCollitionFloor
{
public:

	//		�R���X�g���N�^
	MeshCollitionFloor(MeshCollitionManager* meshCollitionManager);

	//		�f�X�g���N�^
	~MeshCollitionFloor();

	/*
	*	���̓����蔻��
	* 
	*	@param	(objectMesh)		�I�u�W�F�N�g���b�V��
	*	@param	(playerPosition)	�v���C���[�̍��W
	*	@return �����������W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& FloorCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	�v���C���[�̑����̓����蔻��
	* 
	*	@param	(objectMesh)		�I�u�W�F�N�g���b�V��
	*/
	void PlayerFootRadian(ObjectMesh* objectMesh);

	/*
	*	�I�u�W�F�N�g�̓����蔻��
	* 
	*	@param	(objectMesh)	�I�u�W�F�N�g���b�V��
	*	@param	(index)			�v�f
	*/
	void ObjectCollider(ObjectMesh* objectMesh, int index);

	/*
	*	�����ǂ������f����
	* 
	*	@param	(normalize)	�@��
	*	@return �����ǂ��� true : �� false : ���ł͂Ȃ�
	*/
	bool FloorJudgement(const DirectX::SimpleMath::Vector3& normalize);

	/*
	*	�v���C���[�Ƃ̋���
	* 
	*	@return ���ɓ������Ă��邩�ǂ���
	*/
	bool DistancePlayer();

	/*
	*	�v���C���[�̑����̃��C�̍쐻
	*
	*	@param	(vertex)	���_
	*/
	void CreateFootRay(std::vector<DirectX::SimpleMath::Vector3> vertex);

	/*
	*	���̓����蔻��̏���������
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void FloorCollitionInitalize(const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	�v���C���[�ƃ��b�V���̋������ŏ��̒l���o��
	* 
	*/
	void MinLengthMP();

	//		�I������
	void Finalize();

private:

	MeshCollitionManager* m_meshCollitionManager;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		���C�̃X�^�[�g���W
	DirectX::SimpleMath::Vector3 m_rayStart;

	//		���C�̏I�����W
	DirectX::SimpleMath::Vector3 m_rayEnd;

	//		���C�̉������̒���
	float m_rayUnderLength;

	//		���C�̏�����̒���
	float m_rayAboveLength;

	//		�������Ă���|�C���g
	DirectX::SimpleMath::Vector3 m_hitPoint;

	//		���b�V���ɓ������Ă���|�C���g
	std::vector<DirectX::SimpleMath::Vector3> m_hitMeshPoint;

	//		���b�V���ɓ��������@��
	std::vector<DirectX::SimpleMath::Vector3> m_normalize;

	//		�ߋ��̍��W
	DirectX::SimpleMath::Vector3 m_pastPosition;

	//		���b�V���ƃv���C���[�̒���
	float m_minLengthMP;

public:

	/*
	*	���C�̒�����ݒ肷��
	* 
	*	@param	(under)	�������̒���
	*	@param	(above)	������̒���
	*/
	void SetRayLength(float under, float above) 
	{
		m_rayUnderLength = under;
		m_rayAboveLength = above;
	};

	/*
	*	�@�����󂯎��
	* 
	*	@return �@��
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetNormalize() { return m_normalize; }

	/*
	*	�ߋ��̃v���C���[�̍��W���󂯎��
	* 
	*	@param	(position)	���W
	*/
	void SetPastPlayerPosition(DirectX::SimpleMath::Vector3 position) { m_pastPosition = position; }
};