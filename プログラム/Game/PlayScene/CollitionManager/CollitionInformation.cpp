/*
* @file		CollitionInformation.h
* @brief	当たり判定の情報
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
	//		床に当たっていない場合処理をしない
	if (floorhitPoint.size() == 0) return;

	//		床にあたっているポイントがない場合
	if (m_floorhitPoint.size() == 0)
	{
		//		ポイントを追加する
		m_floorhitPoint.push_back(floorhitPoint[0]);
		m_floorNormalize.push_back(floorNormalize[0]);

		return;
	}

	//		今の床が他のオブジェクトの床より近い場合
	if ((floorhitPoint[0] - playerPosition).Length() <
		(m_floorhitPoint[0] - playerPosition).Length())
	{
		//		一番近い床を切り替える
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

	//		壁に当たっていない場合処理をしない
	if (wallHitVelocity.size() == 0) return playerPosition;

	DirectX::SimpleMath::Vector2 playerPositionV2 = { playerPosition.x, playerPosition.z };

	//		壁にあたっているポイントがない場合
	if (m_wallHitVelocity.size() == 0)
	{
		//		ポイントを追加する
		m_wallHitVelocity.push_back(wallHitVelocity[0]);
	}
	else
	{
		//		ポイントを変更する
		m_wallHitVelocity[0] = wallHitVelocity[0];
	}

	//		壁に当たった法線を受け取る
	for (int i = 0; i < wallHitNormalize.size(); ++i)
	{
		//		壁の法線を受け取る
		m_wallHitNormalize.push_back(wallHitNormalize[i]);
	}

	//		現在のプレイヤーの位置を変える
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

