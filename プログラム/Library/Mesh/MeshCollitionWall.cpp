/*
* @file		MeshCollitionWall.cpp
* @brief	メッシュの当たり判定壁
* @author	Morita
* @date		2024/04/28
*/

#include "pch.h"

#include "MeshCollitionWall.h"

#include "MeshCollitionManager.h"

MeshCollitionWall::MeshCollitionWall(MeshCollitionManager* meshCollitionManager)
	:
	m_meshCollitionManager(meshCollitionManager)
{
}

MeshCollitionWall::~MeshCollitionWall()
{
}

std::vector<DirectX::SimpleMath::Vector2> MeshCollitionWall::WallCollition(ObjectMesh* objectMesh,
	const DirectX::SimpleMath::Vector3& playerPosition, float height)
{
	m_playerPosition = playerPosition;

	//		0以外の時削除する
	if (m_normalize.size() != 0) m_normalize.clear();

	m_wallHitJudgement = false;

	for (int i = 0, max = static_cast<int>(objectMesh->GetObjectMesh().size()); i < max; ++i)
	{
		if (!m_meshCollitionManager->GetCommon()->PlayerObjectDirection(objectMesh, playerPosition, i)) continue;

		ObjectCollider(objectMesh, i, height);
	}

	//		0以外の時削除する
	if (m_moveVelocity.size() != 0) m_moveVelocity.clear();

	//		壁と当たっている場合
	if (m_wallHitJudgement)
	{
		m_moveVelocity.push_back({ m_playerPosition.x, m_playerPosition.z });
	}

	return m_moveVelocity;
}

void MeshCollitionWall::ObjectCollider(ObjectMesh* objectMesh, int index, float height)
{
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetObjectMesh()[index].size(); ++i)
	{
		//		壁かどうか判断する
		if (!WallJudgement(objectMesh->GetObjectMesh()[index][i].m_normalVector)) continue;

		//		頂点の座標を受け取る
		vertex[0] = objectMesh->GetObjectMesh()[index][i].m_vertex[0];
		vertex[1] = objectMesh->GetObjectMesh()[index][i].m_vertex[1];
		vertex[2] = objectMesh->GetObjectMesh()[index][i].m_vertex[2];

		//		カメラ分の高さを足す
		height += 0.5f;

		//		円の当たり判定
		if (!m_meshCollitionManager->GetCommon()->CollitionCC(vertex, m_playerPosition, height)) continue;

		//		壁の高さの当たり判定
		if (!WallHeight(vertex, height)) continue;

		//		レイの開始地点
		m_rayStart = m_playerPosition;

		//		テスト
		m_rayStart.y = RayY(vertex, m_playerPosition, height);

		//m_rayStart.y = std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y));

		//m_rayStart.y += 0.01f;

		//m_rayStart.y += 0.5f;

		if (m_rayStart.y > m_playerPosition.y + height)
		{
			continue;
		}

		m_rayEnd = m_rayStart;

		m_rayEnd += -objectMesh->GetObjectMesh()[index][i].m_normalVector * 2.0f;

		//		同一平面上にいるかどうか
		if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
		{
			//		貫通時の処理

			//		過去の座標をレイの開始位置にする
			m_rayStart = m_pastPosition;

			//		同一平面上にいるかどうか
			if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
				objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
			{
				continue;
			}
			else
			{
				//		メッシュの三角形の内側かどうか
				if (!m_meshCollitionManager->GetCommon()->InsideTriangle(vertex,
					objectMesh->GetObjectMesh()[index][i].m_normalVector,
					m_hitPoint)) continue;

				m_playerPosition.x = m_hitPoint.x + objectMesh->GetObjectMesh()[index][i].m_normalVector.x * 2.0f;
				m_playerPosition.z = m_hitPoint.z + objectMesh->GetObjectMesh()[index][i].m_normalVector.z * 2.0f;

				m_normalize.push_back(objectMesh->GetObjectMesh()[index][i].m_normalVector);

				m_wallHitJudgement = true;
			}
		}
		else
		{

			//		メッシュの三角形の内側かどうか
			if (!m_meshCollitionManager->GetCommon()->InsideTriangle(vertex,
				objectMesh->GetObjectMesh()[index][i].m_normalVector,
				m_hitPoint)) continue;

			//		個々の中にいる場合当たっている
			if (!Extrusion(objectMesh->GetObjectMesh()[index][i].m_normalVector)) continue;

			//		当たっている
			m_wallHitJudgement = true;
		}
	}
}

bool MeshCollitionWall::WallJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		上向きの法線に対して+-45度のものは壁とする
	if (DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).Dot(normalize) >= 0.5f ||
		DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).Dot(normalize) <= -0.5f)
	{
		//		壁ではない
		return false;
	}

	return true;
}

bool MeshCollitionWall::WallHeight(const std::vector<DirectX::SimpleMath::Vector3>& vertex, float height)
{
	//		プレイヤーがメッシュの高さ内にいない場合処理をしない
	if (std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y)) <= m_playerPosition.y + 0.3f  ||
		std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y)) >= m_playerPosition.y + height)
	{
		//		壁の高さ外
		return false;
	}

	//		壁の高さ内
	return true;
}

bool MeshCollitionWall::Extrusion(const DirectX::SimpleMath::Vector3& normalize)
{
	//		当たったポイントとプレイヤーの座標の長さ
	float length = (m_rayStart - m_hitPoint).Length();

	//		距離がプレイヤーの半径より大きければ処理をしない
	if (length > 2.0f)
	{
		return false;
	}

	//		法線を二次元にする
	DirectX::SimpleMath::Vector2 normalizeV2 = { normalize.x, normalize.z };
	//		正規化する
	normalizeV2.Normalize();

	//		値が距離以上にならないようにする
	float change = Library::Clamp(length, 0.0f, 2.0f);

	change *= 0.5f;

	//		変化量
	normalizeV2 *= Library::Lerp(2.0f, 0.0f, change);

	//		めり込んだ分移動させる
	m_playerPosition.x += normalizeV2.x;
	m_playerPosition.z += normalizeV2.y;

	m_normalize.push_back(normalize);

	return true;
}

std::vector<DirectX::SimpleMath::Vector3>& MeshCollitionWall::WallWalk
(ObjectMesh* objectMesh, const DirectX::SimpleMath::Vector3& playerPosition)
{
	//		サイズが０ではない時削除する
	if (m_hitpp.size() != 0) m_hitpp.clear();

	for (int i = 0, max = static_cast<int>(objectMesh->GetObjectMesh().size()); i < max; ++i)
	{
		if (!m_meshCollitionManager->GetCommon()->PlayerObjectDirection(objectMesh, playerPosition, i)) continue;

		WallWalkCollider(objectMesh, playerPosition, i);
	}

	if (m_hitpp.size() == 1)
	{
		DirectX::SimpleMath::Vector3 pplayerPosition = { m_meshCollitionManager->GetWallWalkNormalize().x,
			0.0f, m_meshCollitionManager->GetWallWalkNormalize().z };

		pplayerPosition *= 2.0f;

		m_hitpp[0] += pplayerPosition;
	}

	return m_hitpp;
}

void MeshCollitionWall::WallWalkCollider(ObjectMesh* objectMesh,
										const DirectX::SimpleMath::Vector3& playerPosition,
										int index)
{
	//		この値から法線を作成する
	m_meshCollitionManager->GetWallWalkNormalize();

	DirectX::SimpleMath::Vector2 normalize =
	{ m_meshCollitionManager->GetWallWalkNormalize().x,
		m_meshCollitionManager->GetWallWalkNormalize().z };

	normalize.Normalize();

	normalize *= -1;

	//		レイの開始
	DirectX::SimpleMath::Vector3 rayStart = playerPosition;

	//		レイの終了
	DirectX::SimpleMath::Vector3 rayEnd = playerPosition;

	normalize *= 3.0f;

	rayEnd += {normalize.x, 0.0f, normalize.y};

	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetObjectMesh()[index].size(); ++i)
	{
		//		壁かどうか判断する
		if (!WallJudgement(objectMesh->GetObjectMesh()[index][i].m_normalVector)) continue;

		//		頂点の座標を受け取る
		vertex[0] = objectMesh->GetObjectMesh()[index][i].m_vertex[0];
		vertex[1] = objectMesh->GetObjectMesh()[index][i].m_vertex[1];
		vertex[2] = objectMesh->GetObjectMesh()[index][i].m_vertex[2];

		//		プレイーの伸長より小さい場合処理をしない
		if (std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y)) - std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y)) < 7.0f)
		{
			continue;
		}

		//		円の当たり判定が当たっていない場合これ以上処理をしない
		if (!m_meshCollitionManager->GetCommon()->CollitionCC(vertex, rayStart, 2.0f))continue;

		//		同一平面上にいるかどうか
		if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, rayStart, rayEnd,
			objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_wallWalkHitPoint)) continue;

		//		メッシュの三角形の内側かどうか
		if (m_meshCollitionManager->GetCommon()->InsideTriangle(vertex,
			objectMesh->GetObjectMesh()[index][i].m_normalVector,
			m_wallWalkHitPoint))
		{
			//		当たっている部分を追加する
			m_hitpp.push_back(m_wallWalkHitPoint);
		}
	}
}

bool MeshCollitionWall::LinePointHit(
	DirectX::SimpleMath::Vector3 point,
	DirectX::SimpleMath::Vector3 lineA,
	DirectX::SimpleMath::Vector3 lineB,
	DirectX::SimpleMath::Vector3* ans)
{
	DirectX::SimpleMath::Vector3 lineAB = lineB - lineA;
	DirectX::SimpleMath::Vector3 linePA = point - lineA;

	float t = linePA.Dot(lineAB) / lineAB.LengthSquared();

	//		線の向きの外に行った場合処理をしない
	if (t < 0.0f || t > 1.0f)
	{
		return false;
	}

	*ans = lineA + t * lineAB;

	return true;
}

float MeshCollitionWall::RayY(std::vector<DirectX::SimpleMath::Vector3> vertex,
							  DirectX::SimpleMath::Vector3 position,
							  float height)
{
	std::vector<DirectX::SimpleMath::Vector3> hitLine;
	std::vector<DirectX::SimpleMath::Vector3> centerDirection;

	DirectX::SimpleMath::Vector3 point = position;

	DirectX::SimpleMath::Vector3 ans;

	DirectX::SimpleMath::Vector3 center = (vertex[0] + vertex[1] + vertex[2]) / 3.0f;

	for (int i = 0; i < vertex.size(); ++i)
	{
		int val = i + 1;

		if (i == 2)
		{
			val = 0;
		}

		if (LinePointHit(point, vertex[i], vertex[val], &ans))
		{
			DirectX::SimpleMath::Vector3 direction = center - ans;

			direction.Normalize();

			centerDirection.push_back(direction);

			hitLine.push_back(ans);
		}
	}
	
	if (hitLine.size() == 2)
	{
		return PerpendicularPointSecond(hitLine[0].y,
										hitLine[1].y,
										position.y,
										position.y + height);
	}

	if (hitLine.size() == 1)
	{
		return hitLine[0].y;
	}

	return position.y;
}

float MeshCollitionWall::PerpendicularPointSecond(
									float point1,
									float point2,
									float playerUnder,
									float playerHeight)
{
	//		オブジェクト(上) > プレイヤ(上)
	if (std::max(point1, point2) > playerHeight)
	{
		//		オブジェクト(下) < プレイヤ(下)
		if (std::min(point1, point2) < playerUnder)
		{
			//		プレイヤの中心の高さ
			return (playerUnder + playerHeight) / 2.0f;
		}
		//		オブジェクト(下) > プレイヤ(下)
		else
		{
			//		オブジェクト(下)とプレイヤ(上)の中心の高さ
			return (std::min(point1, point2) + playerHeight) / 2.0f;
		}
	}
	//		オブジェクト(上) < プレイヤ(上)
	else
	{
		//		オブジェクト(下) < プレイヤ(下)
		if (std::min(point1, point2) < playerUnder)
		{
			//		オブジェクト(上)とプレイヤ(下)の中心の高さ
			return (std::max(point1, point2) + playerUnder) / 2.0f;
		}
		//		オブジェクト(下) > プレイヤ(下)
		else
		{
			//		オブジェクトの中心高さ
			return (point1 + point2) / 2.0f;
		}
	}
}

void MeshCollitionWall::Finalize()
{
	m_hitpp.clear();
	m_hitpp.shrink_to_fit();
	m_normalize.clear();
	m_normalize.shrink_to_fit();
	m_moveVelocity.clear();
	m_moveVelocity.shrink_to_fit();
}

