/*
* @file		MeshCollitionWall.cpp
* @brief	���b�V���̓����蔻���
* @author	Morita
* @date		2024/04/28
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionManager;

class MeshCollitionWall
{
public:

	MeshCollitionWall(MeshCollitionManager* meshCollitionManager);

	~MeshCollitionWall();

	/*
	*	�ǂ̓����蔻��
	* 
	*	@param	(objectMesh)		�I�u�W�F�N�g���b�V��
	*	@param	(playerPosition)	�v���C���[�̍��W
	*	@param	(height)	�v���C���[�̍���
	*/
	std::vector<DirectX::SimpleMath::Vector2> WallCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		float height);

	/*
	*	�I�u�W�F�N�g�̓����蔻��
	*
	*	@param	(objectMesh)	�I�u�W�F�N�g���b�V��
	*	@param	(index)			�v�f
	*/
	void ObjectCollider(ObjectMesh* objectMesh, int index, float height);
	
	/*
	*	�ǂɓ����������̖@��
	*
	*	@return �@��
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetNormalize() { return m_normalize; }

	/*
	*	�ǂ��ǂ������f����
	* 
	*	@param	(normalize)	�@��
	*	@return �ǂ��ǂ��� true : �ǂł��� false : �ǂł͂Ȃ�
	*/
	bool WallJudgement(const DirectX::SimpleMath::Vector3& normalize);

	/*
	*	�ǂ̍����Ƀv���C���[�����邩�ǂ���
	* 
	*	@param	(vertex)	���_
	*	@param	(height)	�v���C���[�̍���
	*	@return �������ɂ��邩�ǂ��� true : ����@false : ���Ȃ�
	*/
	bool WallHeight(const std::vector<DirectX::SimpleMath::Vector3>& vertex, float height);

	bool Extrusion(const DirectX::SimpleMath::Vector3& normalize);

	std::vector<DirectX::SimpleMath::Vector3>& WallWalk(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition);

	void WallWalkCollider(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition, int index);


	/*
	*	�����Ɠ_�̍ŒZ�_
	* 
	*	@param	(point)	�_�̈ʒu
	*	@param	(lineA)	�����̊J�n�ʒu
	*	@param	(lineB)	�����̏I���ʒu
	*	@param	(ans)	�ŒZ�_
	*	@return true : �ŒZ�_������	false: �Ȃ�
	*/
	bool LinePointHit(DirectX::SimpleMath::Vector3 point,
											  DirectX::SimpleMath::Vector3 lineA,
											  DirectX::SimpleMath::Vector3 lineB,
											  DirectX::SimpleMath::Vector3 *ans);

	/*
	*	���C�̂����W���쐬����
	* 
	*	@param	(vertex)	���b�V���̒��_�i�O�p�j
	*	@param	(position)	�v���C���[���W
	*	@return Y���W
	*/
	float RayY(std::vector<DirectX::SimpleMath::Vector3> vertex,
			   DirectX::SimpleMath::Vector3 position, float height);

	/*
	*	���_�i2�j
	* 
	*/
	float PerpendicularPointSecond(float point1,
								   float point2,
								   float playerUnder,
								   float playerHeight);

	//		�I������
	void Finalize();

private:

	MeshCollitionManager* m_meshCollitionManager;

	//		�������Ă���|�C���g
	DirectX::SimpleMath::Vector3 m_hitPoint;

	//		�ړ���
	std::vector<DirectX::SimpleMath::Vector2> m_moveVelocity;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		�@��
	std::vector<DirectX::SimpleMath::Vector3> m_normalize;

	//		�Ǖ����̃|�C���g
	DirectX::SimpleMath::Vector3 m_wallWalkHitPoint;

	//		
	std::vector<DirectX::SimpleMath::Vector3> m_hitpp;

	//		���C�̊J�n
	DirectX::SimpleMath::Vector3 m_rayStart;

	//		���C�̏I��
	DirectX::SimpleMath::Vector3 m_rayEnd;

	//		�ߋ��̍��W
	DirectX::SimpleMath::Vector3 m_pastPosition;

	bool m_wallHitJudgement = false;
public:

	/*
	*	�ߋ��̍��W��ݒ肷��
	* 
	*	@param	(position)	���W
	*/
	void SetPastPosition(DirectX::SimpleMath::Vector3 position) { m_pastPosition = position; }
};