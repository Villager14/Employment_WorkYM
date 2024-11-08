/*
* @file		ObjectMesh.cpp
* @brief	オブジェクトのメッシュ
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
	//		メッシュの読み込みを生成する
	m_leadMesh = std::make_unique<LeadMesh>();
}

ObjectMesh::~ObjectMesh()
{
}

void ObjectMesh::Initialize(const wchar_t* filePath)
{
	//		読み込む
	m_leadMesh->Lead(filePath);

	//		オブジェクトメッシュを受け取る
	m_objectMesh = m_leadMesh->GetObjectMesh();

	//		メッシュの長さを受け取る
	m_meshLength = m_leadMesh->GetMesnLength();

	//		メッシュの中心を受け取る
	m_meshCenter = m_leadMesh->GetMeshCenter();

	//		リソースの開放(今後使わないので)
	m_leadMesh.reset();
}

void ObjectMesh::StaticProcess(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Vector3& move)
{
	//		静的なオブジェクト
	m_staticObjectJudgement = true;

	//		オブジェクトの初期移動
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

	//		中心位置も変更
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

