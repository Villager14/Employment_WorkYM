/*
* @file		MeshCollitionWall.cpp
* @brief	メッシュの当たり判定壁
* @author	Morita
* @date		2024/04/28
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionManager;

class MeshCollitionWall
{
public:

	MeshCollitionWall(MeshCollitionManager* meshCollitionManager);

	~MeshCollitionWall();

	/*
	*	壁の当たり判定
	* 
	*	@param	(objectMesh)		オブジェクトメッシュ
	*	@param	(playerPosition)	プレイヤーの座標
	*	@param	(height)	プレイヤーの高さ
	*/
	std::vector<DirectX::SimpleMath::Vector2> WallCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		float height);

	/*
	*	オブジェクトの当たり判定
	*
	*	@param	(objectMesh)	オブジェクトメッシュ
	*	@param	(index)			要素
	*/
	void ObjectCollider(ObjectMesh* objectMesh, int index, float height);
	
	/*
	*	壁に当たった時の法線
	*
	*	@return 法線
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetNormalize() { return m_normalize; }

	/*
	*	壁かどうか判断する
	* 
	*	@param	(normalize)	法線
	*	@return 壁かどうか true : 壁である false : 壁ではない
	*/
	bool WallJudgement(const DirectX::SimpleMath::Vector3& normalize);

	/*
	*	壁の高さにプレイヤーがいるかどうか
	* 
	*	@param	(vertex)	頂点
	*	@param	(height)	プレイヤーの高さ
	*	@return 高さ内にいるかどうか true : いる　false : いない
	*/
	bool WallHeight(const std::vector<DirectX::SimpleMath::Vector3>& vertex, float height);

	bool Extrusion(const DirectX::SimpleMath::Vector3& normalize);

	std::vector<DirectX::SimpleMath::Vector3>& WallWalk(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition);

	void WallWalkCollider(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition, int index);


	/*
	*	線分と点の最短点
	* 
	*	@param	(point)	点の位置
	*	@param	(lineA)	線分の開始位置
	*	@param	(lineB)	線分の終了位置
	*	@param	(ans)	最短点
	*	@return true : 最短点がある	false: ない
	*/
	bool LinePointHit(DirectX::SimpleMath::Vector3 point,
											  DirectX::SimpleMath::Vector3 lineA,
											  DirectX::SimpleMath::Vector3 lineB,
											  DirectX::SimpleMath::Vector3 *ans);

	/*
	*	レイのｙ座標を作成する
	* 
	*	@param	(vertex)	メッシュの頂点（三角）
	*	@param	(position)	プレイヤー座標
	*	@return Y座標
	*/
	float RayY(std::vector<DirectX::SimpleMath::Vector3> vertex,
			   DirectX::SimpleMath::Vector3 position, float height);

	/*
	*	垂点（2）
	* 
	*/
	float PerpendicularPointSecond(float point1,
								   float point2,
								   float playerUnder,
								   float playerHeight);

	//		終了処理
	void Finalize();

private:

	MeshCollitionManager* m_meshCollitionManager;

	//		当たっているポイント
	DirectX::SimpleMath::Vector3 m_hitPoint;

	//		移動量
	std::vector<DirectX::SimpleMath::Vector2> m_moveVelocity;

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		法線
	std::vector<DirectX::SimpleMath::Vector3> m_normalize;

	//		壁歩きのポイント
	DirectX::SimpleMath::Vector3 m_wallWalkHitPoint;

	//		
	std::vector<DirectX::SimpleMath::Vector3> m_hitpp;

	//		レイの開始
	DirectX::SimpleMath::Vector3 m_rayStart;

	//		レイの終了
	DirectX::SimpleMath::Vector3 m_rayEnd;

	//		過去の座標
	DirectX::SimpleMath::Vector3 m_pastPosition;

	bool m_wallHitJudgement = false;
public:

	/*
	*	過去の座標を設定する
	* 
	*	@param	(position)	座標
	*/
	void SetPastPosition(DirectX::SimpleMath::Vector3 position) { m_pastPosition = position; }
};