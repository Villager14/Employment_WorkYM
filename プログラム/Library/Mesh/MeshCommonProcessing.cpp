/*
* @file		MeshCommonProcessing.cpp
* @brief	メッシュの共通処理
* @author	Morita
* @date		2024/07/30
*/

#include "pch.h"

#include"MeshCommonProcessing.h"

MeshCommonProcessing::MeshCommonProcessing()
{
}

MeshCommonProcessing::~MeshCommonProcessing()
{
}

bool MeshCommonProcessing::CollitionCC(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& playerPos, const float& playerLength)
{
	//		メッシュの最大の辺の長さを求める
	float meshLength = std::max((vertex[0] - vertex[1]).Length(),
		std::max((vertex[0] - vertex[2]).Length(),
			(vertex[1] - vertex[2]).Length()));

	//		メッシュの中心点を求める
	DirectX::SimpleMath::Vector3 m_centerPoint = (vertex[0] + vertex[1] + vertex[2]) / 3.0f;

	//		プレイヤーとメッシュの中心の座標がメッシュの長さとプレイヤーのレイの長さより小さい時
	if ((m_centerPoint - playerPos).Length() <= meshLength + playerLength)
	{
		//		当たっている
		return true;
	}

	//		当たっていない
	return false;
}

bool MeshCommonProcessing::OnTheSamePlane(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& rayStart, const DirectX::SimpleMath::Vector3& rayEnd,
	const DirectX::SimpleMath::Vector3& normalize, DirectX::SimpleMath::Vector3* hitPoint)
{
	//		三角形の中心を求める
	DirectX::SimpleMath::Vector3 center =
		(vertex[0] + vertex[1] + vertex[2]) / 3;

	//		レイの方向に向いているベクトルを出す
	DirectX::SimpleMath::Vector3 velocityS = rayStart - center;
	DirectX::SimpleMath::Vector3 velocityE = rayEnd - center;

	//		内積を取る
	float dotS = normalize.Dot(velocityS);
	float dotE = normalize.Dot(velocityE);

	//		値が０以下の場合処理をしない
	if (dotS * dotE <= 0)
	{
		//		平面上の点を求める
		float m = abs(dotS);
		float n = abs(dotE);

		//		当たっているポイント
		*hitPoint = (rayStart * n + rayEnd * m) / (m + n);

		//		含まれている
		return true;
	}

	//		含まれていない
	return false;
}

bool MeshCommonProcessing::InsideTriangle(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& normalize, const DirectX::SimpleMath::Vector3& hitPoint)
{
	for (int i = 0; i < 3; ++i)
	{
		//		当たった座標に向かうベクトル
		DirectX::SimpleMath::Vector3 hitVelocity = hitPoint - vertex[i];

		//		別の頂点に向かうベクトル
		DirectX::SimpleMath::Vector3 meshVelocity = vertex[(i + 2) % 3] - vertex[i];

		//		外積を求める
		DirectX::SimpleMath::Vector3 cross = hitVelocity.Cross(meshVelocity);

		//		正規化
		cross.Normalize();

		//		法線と外積の内積を取る
		float d = normalize.Dot(cross);

		//		0以下の場合三角形の外側にいる
		if (d < 0)
		{
			//		外側
			return false;
		}
	}

	//		内側
	return true;
}

bool MeshCommonProcessing::PlayerObjectDirection(ObjectMesh* objectMesh,
	DirectX::SimpleMath::Vector3 playerPosition, int index)
{
	//		プレイヤーとメッシュの距離
	float length = (objectMesh->GetMeshCenter()[index] - playerPosition).Length();

	if (length - 7.0f < objectMesh->GetMesnLength()[index])
	{
		return true;
	}

	return false;
}