/*
* @file		ObjectMesh.cpp
* @brief	�I�u�W�F�N�g�̃��b�V��
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "ObjectMesh.h"

#include <fstream>

#include <Effects.h>

ObjectMesh::ObjectMesh()
	:
	m_staticObjectJudgement(false),
	m_objectType{ObjectType::Null}
{
	//		���b�V���̓ǂݍ��݂𐶐�����
	m_leadMesh = std::make_unique<LeadMesh>();
}

ObjectMesh::~ObjectMesh()
{
}

void ObjectMesh::Initialize(const wchar_t* filePath)
{
	//		�ǂݍ���
	m_leadMesh->Lead(filePath);

	//		�I�u�W�F�N�g���b�V�����󂯎��
	m_objectMesh = m_leadMesh->GetObjectMesh();

	//		���b�V���̒������󂯎��
	m_meshLength = m_leadMesh->GetMesnLength();

	//		���b�V���̒��S���󂯎��
	m_meshCenter = m_leadMesh->GetMeshCenter();

	//		���\�[�X�̊J��(����g��Ȃ��̂�)
	m_leadMesh.reset();
}

void ObjectMesh::StaticProcess(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Vector3& move)
{
	//		�ÓI�ȃI�u�W�F�N�g
	m_staticObjectJudgement = true;

	//		�I�u�W�F�N�g�̏����ړ�
	for (int i = 0, max = static_cast<int>(m_objectMesh.size()); i < max; ++i)
	{
		for (int j = 0, jMax = static_cast<int>(m_objectMesh[i].size()); j < jMax; ++j)
		{
			m_objectMesh[i][j].m_vertex[0] = DirectX::SimpleMath::Vector3::Transform(m_objectMesh[i][j].m_vertex[0], world);
			m_objectMesh[i][j].m_vertex[1] = DirectX::SimpleMath::Vector3::Transform(m_objectMesh[i][j].m_vertex[1], world);
			m_objectMesh[i][j].m_vertex[2] = DirectX::SimpleMath::Vector3::Transform(m_objectMesh[i][j].m_vertex[2], world);

			m_objectMesh[i][j].m_vertex[0] += move;
			m_objectMesh[i][j].m_vertex[1] += move;
			m_objectMesh[i][j].m_vertex[2] += move;

			m_objectMesh[i][j].m_normalVector = DirectX::SimpleMath::Vector3::Transform(m_objectMesh[i][j].m_normalVector, world);
		}
	}

	//		���S�ʒu���ύX
	for (int i = 0; i < m_meshCenter.size(); ++i)
	{
		m_meshCenter[i] += move;
	}
}

void ObjectMesh::Finalize()
{
	m_objectMesh.clear();
	m_meshLength.clear();
	m_meshCenter.clear();
}

