/*
* @file		MeshCollitionHead.h
* @brief	メッシュの当たり判定頭
* @author	Morita
* @date		2024/07/22
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionManager;

class MeshCollitionHead
{
public:

	//		コンストラクタ
	MeshCollitionHead(MeshCollitionManager* meshCollitionManager);

	//		デストラクタ
	~MeshCollitionHead();

	void HeadCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		const float playerHeight);

	//		天井かどうか
	bool CeilingJudgement(const DirectX::SimpleMath::Vector3& normalize);

	/*
	*	オブジェクトの当たり判定
	*
	*	@param	(objectMesh)	オブジェクトメッシュ
	*	@param	(index)			要素
	*/
	void ObjectCollider(ObjectMesh* objectMesh, int index);

	/*
	*	頭の初期化処理
	*
	*	@param	(playerPosition)	プレイヤーの座標
	*	@param	(playerHeight)		プレイヤーの高さ
	*/
	void HeightCollitionInitalize(const DirectX::SimpleMath::Vector3& playerPosition,
								 const float playerHeight);

private:

	MeshCollitionManager* m_meshCollitionManager;

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		レイのスタート座標
	DirectX::SimpleMath::Vector3 m_rayStart;

	//		レイの終了座標
	DirectX::SimpleMath::Vector3 m_rayEnd;

	//		当たっているポイント
	DirectX::SimpleMath::Vector3 m_hitPoint;

	//		当たっているかどうか
	bool m_hitJudgement;

public:

	bool GetHitJudgement() { return m_hitJudgement; }
};