/*
* @file		CollitionInformation.h
* @brief	�����蔻��̏��
* @author	Morita
* @date		2024/05/16
*/

#include "pch.h"

#include "CollitionInformation.h"

CollitionInformation::CollitionInformation()
	:
	m_ceilingHitJudgement(false)
{
}

CollitionInformation::~CollitionInformation()
{
}

void CollitionInformation::Clear()
{
	m_floorhitPoint.clear();
	m_floorNormalize.clear();
	m_wallHitVelocity.clear();
	m_wallHitNormalize.clear();
	m_wallWalkPosition.clear();
	m_ceilingHitJudgement = false;
}

void CollitionInformation::FloorMeshInformation(
	const std::vector<DirectX::SimpleMath::Vector3>& floorhitPoint,
	const std::vector<DirectX::SimpleMath::Vector3>& floorNormalize,
	const DirectX::SimpleMath::Vector3& playerPosition)
{
	//		���ɓ������Ă��Ȃ��ꍇ���������Ȃ�
	if (floorhitPoint.size() == 0) return;

	//		���ɂ������Ă���|�C���g���Ȃ��ꍇ
	if (m_floorhitPoint.size() == 0)
	{
		//		�|�C���g��ǉ�����
		m_floorhitPoint.push_back(floorhitPoint[0]);
		m_floorNormalize.push_back(floorNormalize[0]);

		return;
	}

	//		���̏������̃I�u�W�F�N�g�̏����߂��ꍇ
	if ((floorhitPoint[0] - playerPosition).Length() <
		(m_floorhitPoint[0] - playerPosition).Length())
	{
		//		��ԋ߂�����؂�ւ���
		m_floorhitPoint[0] = floorhitPoint[0];
		m_floorNormalize[0] = floorNormalize[0];
	}

}

DirectX::SimpleMath::Vector3 CollitionInformation::WallMeshInformation
(const std::vector<DirectX::SimpleMath::Vector2>& wallHitVelocity,
 const std::vector<DirectX::SimpleMath::Vector3>& wallHitNormalize,
 const std::vector<DirectX::SimpleMath::Vector3>& wallWalkPosition,
 const DirectX::SimpleMath::Vector3& playerPosition)
{
	if (wallWalkPosition.size() != 0)
		m_wallWalkPosition = wallWalkPosition;

	//		�ǂɓ������Ă��Ȃ��ꍇ���������Ȃ�
	if (wallHitVelocity.size() == 0) return playerPosition;

	DirectX::SimpleMath::Vector2 playerPositionV2 = { playerPosition.x, playerPosition.z };

	//		�ǂɂ������Ă���|�C���g���Ȃ��ꍇ
	if (m_wallHitVelocity.size() == 0)
	{
		//		�|�C���g��ǉ�����
		m_wallHitVelocity.push_back(wallHitVelocity[0]);
	}
	else
	{
		//		�|�C���g��ύX����
		m_wallHitVelocity[0] = wallHitVelocity[0];
	}

	//		�ǂɓ��������@�����󂯎��
	for (int i = 0; i < wallHitNormalize.size(); ++i)
	{
		//		�ǂ̖@�����󂯎��
		m_wallHitNormalize.push_back(wallHitNormalize[i]);
	}

	//		���݂̃v���C���[�̈ʒu��ς���
	return { playerPositionV2.x, playerPosition.y ,playerPositionV2.y };
}

void CollitionInformation::Finalize()
{
	m_floorhitPoint.clear();
	m_floorhitPoint.shrink_to_fit();
	m_floorNormalize.clear();
	m_floorNormalize.shrink_to_fit();
	m_wallHitVelocity.clear();
	m_wallHitVelocity.shrink_to_fit();
	m_wallHitNormalize.clear();
	m_wallHitNormalize.shrink_to_fit();
	m_wallWalkPosition.clear();
	m_wallWalkPosition.shrink_to_fit();
}

