/*
* @file		MeshCollitionFloor.h
* @brief	メッシュの当たり判定床
* @author	Morita
* @date		2024/04/27
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionManager;

class MeshCollitionFloor
{
public:

	//		コンストラクタ
	MeshCollitionFloor(MeshCollitionManager* meshCollitionManager);

	//		デストラクタ
	~MeshCollitionFloor();

	/*
	*	床の当たり判定
	* 
	*	@param	(objectMesh)		オブジェクトメッシュ
	*	@param	(playerPosition)	プレイヤーの座標
	*	@return 当たった座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& FloorCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	プレイヤーの足元の当たり判定
	* 
	*	@param	(objectMesh)		オブジェクトメッシュ
	*/
	void PlayerFootRadian(ObjectMesh* objectMesh);

	/*
	*	オブジェクトの当たり判定
	* 
	*	@param	(objectMesh)	オブジェクトメッシュ
	*	@param	(index)			要素
	*/
	void ObjectCollider(ObjectMesh* objectMesh, int index);

	/*
	*	床かどうか判断する
	* 
	*	@param	(normalize)	法線
	*	@return 床かどうか true : 床 false : 床ではない
	*/
	bool FloorJudgement(const DirectX::SimpleMath::Vector3& normalize);

	/*
	*	プレイヤーとの距離
	* 
	*	@return 床に当たっているかどうか
	*/
	bool DistancePlayer();

	/*
	*	プレイヤーの足元のレイの作製
	*
	*	@param	(vertex)	頂点
	*/
	void CreateFootRay(std::vector<DirectX::SimpleMath::Vector3> vertex);

	/*
	*	床の当たり判定の初期化処理
	* 
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void FloorCollitionInitalize(const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	プレイヤーとメッシュの距離が最小の値を出す
	* 
	*/
	void MinLengthMP();

	//		終了処理
	void Finalize();

private:

	MeshCollitionManager* m_meshCollitionManager;

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		レイのスタート座標
	DirectX::SimpleMath::Vector3 m_rayStart;

	//		レイの終了座標
	DirectX::SimpleMath::Vector3 m_rayEnd;

	//		レイの下方向の長さ
	float m_rayUnderLength;

	//		レイの上方向の長さ
	float m_rayAboveLength;

	//		当たっているポイント
	DirectX::SimpleMath::Vector3 m_hitPoint;

	//		メッシュに当たっているポイント
	std::vector<DirectX::SimpleMath::Vector3> m_hitMeshPoint;

	//		メッシュに当たった法線
	std::vector<DirectX::SimpleMath::Vector3> m_normalize;

	//		過去の座標
	DirectX::SimpleMath::Vector3 m_pastPosition;

	//		メッシュとプレイヤーの長さ
	float m_minLengthMP;

public:

	/*
	*	レイの長さを設定する
	* 
	*	@param	(under)	下方向の長さ
	*	@param	(above)	上方向の長さ
	*/
	void SetRayLength(float under, float above) 
	{
		m_rayUnderLength = under;
		m_rayAboveLength = above;
	};

	/*
	*	法線を受け取る
	* 
	*	@return 法線
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetNormalize() { return m_normalize; }

	/*
	*	過去のプレイヤーの座標を受け取る
	* 
	*	@param	(position)	座標
	*/
	void SetPastPlayerPosition(DirectX::SimpleMath::Vector3 position) { m_pastPosition = position; }
};