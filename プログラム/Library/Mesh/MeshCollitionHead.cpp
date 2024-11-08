/*
* @file		MeshCollitionHead.h
* @brief	メッシュの当たり判定頭
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

	//		レイの情報を生成する
	HeightCollitionInitalize(playerPosition, playerHeight + 0.5f);

	for (int i = 0, max = static_cast<int>(objectMesh->GetObjectMesh().size()); i < max; ++i)
	{
		if (!m_meshCollitionManager->GetCommon()->PlayerObjectDirection(objectMesh, playerPosition, i)) continue;

		//		オブジェクトの当たり判定
		ObjectCollider(objectMesh, i);
	}
}

bool MeshCollitionHead::CeilingJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		上向きの法線に対して+-45度のものは壁とする
	if (DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).Dot(normalize) >= -0.5f)
	{
		//		壁ではない
		return false;
	}

	return false;
}

void MeshCollitionHead::ObjectCollider(ObjectMesh* objectMesh, int index)
{
	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetObjectMesh()[index].size(); ++i)
	{
		//		天井かどうか	
		if (CeilingJudgement(objectMesh->GetObjectMesh()[index][i].m_normalVector)) continue;

		//		頂点の座標を受け取る
		vertex[0] = objectMesh->GetObjectMesh()[index][i].m_vertex[0];
		vertex[1] = objectMesh->GetObjectMesh()[index][i].m_vertex[1];
		vertex[2] = objectMesh->GetObjectMesh()[index][i].m_vertex[2];
		
		//		円の当たり判定が当たっていない場合これ以上処理をしない
		if (!m_meshCollitionManager->GetCommon()->CollitionCC(vertex, m_rayStart, 7.0f))continue;
		
		//		同一平面上にいるかどうか
		if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
		{
			//		貫通時の処理

			//		過去の座標をレイの開始位置にする
			//m_rayStart = m_pastPosition;

			//		上にレイを上げる
			//m_rayStart.y += m_rayAboveLength;

			//		同一平面上にいるかどうか
			//if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			//	objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
			//{
			//	continue;
			//}

			continue;
		}

		//		メッシュの三角形の内側かどうか
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

	//		プレイヤーの座標を設定する
	m_playerPosition = playerPosition;

	//		レイの座標１
	m_rayStart = playerPosition;

	//		レイの座標２
	m_rayEnd = m_rayStart;

	//		レイの長さを上げる
	m_rayStart.y += playerHeight - 0.3f;

	//		レイの長さ分下げる
	m_rayEnd.y += playerHeight + 0.5f;
}
