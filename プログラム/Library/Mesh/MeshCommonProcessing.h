/*
* @file		MeshCommonProcessing.h
* @brief	���b�V���̋��ʏ���
* @author	Morita
* @date		2024/07/30
*/

#pragma once

#include "ObjectMesh.h"

class MeshCommonProcessing
{
public:

	//		�R���X�g���N�^
	MeshCommonProcessing();

	//		�f�X�g���N�^
	~MeshCommonProcessing();

	/*
	*	�~�Ɖ~�̓����蔻��
	*
	*	@param	(vertex)	���b�V���̒��_
	*	@param	(playerPos)	�v���C���[�̍��W
	*	@param	(rayStart)	�v���C���[�̒���
	*	@return �����������ǂ��� true : �������� false : �������Ă��Ȃ�
	*/
	bool CollitionCC(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const DirectX::SimpleMath::Vector3& playerPos,
		const float& playerLength);

	/*
	*	���ꕽ�ʏ�ɂ��邩�ǂ���
	*
	*	@param	(vertex)	���b�V���̒��_
	*	@param	(rayStart)	���C�̎n�_
	*	@param	(rayEnd)	���C�̏I�_
	*	@param	(normalize)	���b�V���̖@��
	*	@param	(hitPoint)	���������ꏊ
	*	@return �܂܂�Ă��邩�ǂ���	true : �܂܂�Ă��� false : �܂܂�Ă��Ȃ�
	*/
	bool OnTheSamePlane(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const DirectX::SimpleMath::Vector3& rayStart,
		const DirectX::SimpleMath::Vector3& rayEnd,
		const DirectX::SimpleMath::Vector3& normalize,
		DirectX::SimpleMath::Vector3* hitPoint);

	/*
	*	�O�p�`�̓����ɂ��邩�ǂ���
	*
	*	@param	(vertex)	���b�V���̒��_
	*	@param	(normalize)	���b�V���̖@��
	*	@param	(hitPoint)	���������ꏊ
	*	@return �����ɂ��邩�ǂ��� true : ���� false : �O��
	*/
	bool InsideTriangle(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const DirectX::SimpleMath::Vector3& normalize,
		const DirectX::SimpleMath::Vector3& hitPoint);

	/*
	*	�I�u�W�F�N�g�ƃv���C���[�̋���
	*
	*	@param	(objectMesh)	�I�u�W�F�N�g���b�V��
	*	@return �͈͓����ǂ����H true : �͈͓� false : �͈͊O
	*/
	bool PlayerObjectDirection(ObjectMesh* objectMesh,
		DirectX::SimpleMath::Vector3 playerPosition, int index);

};