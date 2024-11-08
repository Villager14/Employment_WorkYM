/*
* @file		MeshCollitionFloor.cpp
* @brief	メッシュの当たり判定床
* @author	Morita
* @date		2024/04/27
*/

#include "pch.h"

#include "MeshCollitionFloor.h"

#include "MeshCollitionManager.h"

MeshCollitionFloor::MeshCollitionFloor(MeshCollitionManager* meshCollitionManager)
	:
	m_meshCollitionManager(meshCollitionManager),
	m_rayAboveLength(0.0f),
	m_rayUnderLength(0.0f),
	m_minLengthMP(0.0f)
{
}

MeshCollitionFloor::~MeshCollitionFloor()
{
}

const std::vector<DirectX::SimpleMath::Vector3>& MeshCollitionFloor::FloorCollition(
	ObjectMesh* objectMesh, const DirectX::SimpleMath::Vector3& playerPosition)
{
	FloorCollitionInitalize(playerPosition);

	for (int i = 0, max = static_cast<int>(objectMesh->GetObjectMesh().size()); i < max; ++i)
	{
		if (!m_meshCollitionManager->GetCommon()->PlayerObjectDirection(objectMesh, playerPosition, i)) continue;

		//		オブジェクトの当たり判定
		ObjectCollider(objectMesh, i);
	}

	//		メッシュに当たっているか
	if (DistancePlayer()) return m_hitMeshPoint;

	return m_hitMeshPoint;
}

void MeshCollitionFloor::PlayerFootRadian(ObjectMesh* objectMesh)
{
	UNREFERENCED_PARAMETER(objectMesh);

	/*
	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	{
		//		床かどうか判断する
		if (!FloorJudgement(objectMesh->GetNormalizePosition(i))) continue;

		//		頂点の座標を受け取る
		vertex[0] = objectMesh->GetVertexPosition(i, 0);
		vertex[1] = objectMesh->GetVertexPosition(i, 1);
		vertex[2] = objectMesh->GetVertexPosition(i, 2);

		CreateFootRay(vertex);

		//		円の当たり判定が当たっていない場合これ以上処理をしない
		if (!m_meshCollitionManager->CollitionCC(vertex, m_playerPosition, 2.0f))continue;

		//		同一平面上にいるかどうか
		if (!m_meshCollitionManager->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetNormalizePosition(i), &m_hitPoint)) continue;

		//		メッシュの三角形の内側かどうか
		if (m_meshCollitionManager->InsideTriangle(vertex,
			objectMesh->GetNormalizePosition(i),
			m_hitPoint))
		{
			//		当たっている部分を追加する
			m_hitMeshPoint.push_back(m_hitPoint);

			//		プレイヤーとメッシュの最短距離を求める
			MinLengthMP();
		}
	}
	*/
}

void MeshCollitionFloor::ObjectCollider(ObjectMesh* objectMesh, int index)
{
	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetObjectMesh()[index].size(); ++i)
	{
		//		頂点の座標を受け取る
		vertex[0] = objectMesh->GetObjectMesh()[index][i].m_vertex[0];
		vertex[1] = objectMesh->GetObjectMesh()[index][i].m_vertex[1];
		vertex[2] = objectMesh->GetObjectMesh()[index][i].m_vertex[2];

		//		円の当たり判定が当たっていない場合これ以上処理をしない
		if (!m_meshCollitionManager->GetCommon()->CollitionCC(vertex, m_rayStart, 2.0f))continue;

		//		同一平面上にいるかどうか
		if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
		{
			//		貫通時の処理

			//		過去の座標をレイの開始位置にする
			m_rayStart = m_pastPosition;

			//		上にレイを上げる
			m_rayStart.y += m_rayAboveLength;

			//		同一平面上にいるかどうか
			if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
				objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
			{
				continue;
			}
		}

		//		メッシュの三角形の内側かどうか
		if (m_meshCollitionManager->GetCommon()->InsideTriangle(vertex,
			objectMesh->GetObjectMesh()[index][i].m_normalVector,
			m_hitPoint))
		{
			//		当たっている部分を追加する
			m_hitMeshPoint.push_back(m_hitPoint);
			//		法線を追加
			m_normalize.push_back(objectMesh->GetObjectMesh()[index][i].m_normalVector);
		}
	}
}

bool MeshCollitionFloor::FloorJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		上向きの法線とメッシュの法線で内積を取る
	float dot = DirectX::SimpleMath::Vector3(0, 1, 0).Dot(normalize);

	//		法線の方向が上を向いていない場合(45度まで)
	if (dot < 0.5f)
	{
		//		床ではない
		return false;
	}

	return true;
}

bool MeshCollitionFloor::DistancePlayer()
{
	//		当たった座標の数が０以下の時
	if (m_hitMeshPoint.size() <= 0)
	{

		return false;
	}
	//		最もプレイヤーから近い座標
	DirectX::SimpleMath::Vector3 position = m_hitMeshPoint[0];

	//		最もプレイヤーから近い座標とプレイヤーとの距離
	float length = (m_hitMeshPoint[0] - m_playerPosition).Length();

	//		法線
	DirectX::SimpleMath::Vector3 normalize = m_normalize[0];

	//		最もプレイヤーから近い座標を計算する
	for (int i = 0, max = static_cast<int>(m_hitMeshPoint.size()); i < max; ++i)
	{
		//		もし配列の要素数より大きい数字になった場合
		if (i + 1 >= static_cast<int>(m_hitMeshPoint.size()))
		{
			break;
		}

		int indexf = i + 1;

		//		もし現在の最短座標より短かった場合
		if (length <= (m_hitMeshPoint[indexf] - m_playerPosition).Length())
		{
			//		最短座標を更新する
			length = (m_hitMeshPoint[indexf] - m_playerPosition).Length();

			//		最短座標を代入する
			position = m_hitMeshPoint[indexf];

			//		法線を代入する
			normalize = m_normalize[indexf];
		}
	}

	//		当たったポイントの開放
	m_hitMeshPoint.clear();

	//		法線の開放
	m_normalize.clear();

	//		最短座標を代入する
	m_hitMeshPoint.push_back(position);

	//		法線を代入する
	m_normalize.push_back(normalize);

	return true;
}

void MeshCollitionFloor::CreateFootRay(std::vector<DirectX::SimpleMath::Vector3> vertex)
{
	//		メッシュの中心
	DirectX::SimpleMath::Vector3 center =
		(vertex[0] + vertex[1] + vertex[2]) / 3.0f;

	//		中心へ向かうベクトル
	DirectX::SimpleMath::Vector3 velocity = center - m_playerPosition;

	velocity.Normalize();

	velocity *= 2.0f;

	//		レイの座標１
	m_rayStart = velocity + m_playerPosition;

	//		レイの座標２
	m_rayEnd = m_rayStart;

	//		レイの長さを上げる
	m_rayStart.y += m_rayAboveLength;

	//		レイの長さ分下げる
	m_rayEnd.y -= m_rayUnderLength;
}

void MeshCollitionFloor::FloorCollitionInitalize(const DirectX::SimpleMath::Vector3& playerPosition)
{
	//		解放
	m_hitMeshPoint.clear();

	//		解放
	m_normalize.clear();

	m_hitPoint = DirectX::SimpleMath::Vector3::Zero;

	//		プレイヤーの座標を設定する
	m_playerPosition = playerPosition;

	//		レイの座標１
	m_rayStart = playerPosition;

	//		レイの座標２
	m_rayEnd = m_rayStart;

	//		レイの長さを上げる
	m_rayStart.y += m_rayAboveLength;

	//		レイの長さ分下げる
	m_rayEnd.y -= m_rayUnderLength;
}

void MeshCollitionFloor::MinLengthMP()
{
	//		レイの座標を出す
	DirectX::SimpleMath::Vector3 rayPosition = m_rayStart;

	//		レイの原点に戻す
	rayPosition.y -= m_rayAboveLength;

	//		メッシュの数が一つの時
	if (m_hitMeshPoint.size() == 1)
	{
		//		メッシュの長さを保存する
		m_minLengthMP = (m_hitMeshPoint[0] - m_playerPosition).Length();

		//		最短座標を代入する
		m_hitMeshPoint.push_back(m_hitMeshPoint[0]);

		return;
	}

	DirectX::SimpleMath::Vector3 position;

	//		もし現在の最短座標より短かった場合
	if (m_minLengthMP >= (m_hitMeshPoint[1] - rayPosition).Length())
	{
		//		最短座標を更新する
		m_minLengthMP = (m_hitMeshPoint[1] - m_playerPosition).Length();

		//		最短座標を代入する
		position = m_hitMeshPoint[1];
	}

	//		メッシュの削除
	m_hitMeshPoint.clear();

	//		最短座標を代入する
	m_hitMeshPoint.push_back(position);
}

void MeshCollitionFloor::Finalize()
{
	m_hitMeshPoint.clear();
	m_hitMeshPoint.shrink_to_fit();
	m_normalize.clear();
	m_normalize.shrink_to_fit();
}
