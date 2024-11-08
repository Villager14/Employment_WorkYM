/*
* @file		MeshCollitionHead.h
* @brief	���b�V���̓����蔻�蓪
* @author	Morita
* @date		2024/07/22
*/

#include "pch.h"
#include "MeshCollitionHead.h"

#include "MeshCollitionManager.h"

MeshCollitionHead::MeshCollitionHead(MeshCollitionManager* meshCollitionManager)
	:
	m_meshCollitionManager(meshCollitionManager),
	m_hitJudgement(false)
{
}

MeshCollitionHead::~MeshCollitionHead()
{
}

void MeshCollitionHead::HeadCollition(ObjectMesh* objectMesh,
	const DirectX::SimpleMath::Vector3& playerPosition,
	const float playerHeight)
{
	UNREFERENCED_PARAMETER(objectMesh);
	UNREFERENCED_PARAMETER(playerPosition);

	//		���C�̏��𐶐�����
	HeightCollitionInitalize(playerPosition, playerHeight + 0.5f);

	for (int i = 0, max = static_cast<int>(objectMesh->GetObjectMesh().size()); i < max; ++i)
	{
		if (!m_meshCollitionManager->GetCommon()->PlayerObjectDirection(objectMesh, playerPosition, i)) continue;

		//		�I�u�W�F�N�g�̓����蔻��
		ObjectCollider(objectMesh, i);
	}
}

bool MeshCollitionHead::CeilingJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		������̖@���ɑ΂���+-45�x�̂��͕̂ǂƂ���
	if (DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).Dot(normalize) >= -0.5f)
	{
		//		�ǂł͂Ȃ�
		return false;
	}

	return false;
}

void MeshCollitionHead::ObjectCollider(ObjectMesh* objectMesh, int index)
{
	//		���_
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetObjectMesh()[index].size(); ++i)
	{
		//		�V�䂩�ǂ���	
		if (CeilingJudgement(objectMesh->GetObjectMesh()[index][i].m_normalVector)) continue;

		//		���_�̍��W���󂯎��
		vertex[0] = objectMesh->GetObjectMesh()[index][i].m_vertex[0];
		vertex[1] = objectMesh->GetObjectMesh()[index][i].m_vertex[1];
		vertex[2] = objectMesh->GetObjectMesh()[index][i].m_vertex[2];
		
		//		�~�̓����蔻�肪�������Ă��Ȃ��ꍇ����ȏ㏈�������Ȃ�
		if (!m_meshCollitionManager->GetCommon()->CollitionCC(vertex, m_rayStart, 7.0f))continue;
		
		//		���ꕽ�ʏ�ɂ��邩�ǂ���
		if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
		{
			//		�ђʎ��̏���

			//		�ߋ��̍��W�����C�̊J�n�ʒu�ɂ���
			//m_rayStart = m_pastPosition;

			//		��Ƀ��C���グ��
			//m_rayStart.y += m_rayAboveLength;

			//		���ꕽ�ʏ�ɂ��邩�ǂ���
			//if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			//	objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
			//{
			//	continue;
			//}

			continue;
		}

		//		���b�V���̎O�p�`�̓������ǂ���
		if (m_meshCollitionManager->GetCommon()->InsideTriangle(vertex,
			objectMesh->GetObjectMesh()[index][i].m_normalVector,
			m_hitPoint))
		{
			m_hitJudgement = true;
		}
	}
}

void MeshCollitionHead::HeightCollitionInitalize(const DirectX::SimpleMath::Vector3& playerPosition,
												 const float playerHeight)
{
	m_hitJudgement = false;

	//		�v���C���[�̍��W��ݒ肷��
	m_playerPosition = playerPosition;

	//		���C�̍��W�P
	m_rayStart = playerPosition;

	//		���C�̍��W�Q
	m_rayEnd = m_rayStart;

	//		���C�̒������グ��
	m_rayStart.y += playerHeight - 0.3f;

	//		���C�̒�����������
	m_rayEnd.y += playerHeight + 0.5f;
}
