/*
* @file		MeshCommonProcessing.h
* @brief	メッシュの共通処理
* @author	Morita
* @date		2024/07/30
*/

#pragma once

#include "ObjectMesh.h"

class MeshCommonProcessing
{
public:

	//		コンストラクタ
	MeshCommonProcessing();

	//		デストラクタ
	~MeshCommonProcessing();

	/*
	*	円と円の当たり判定
	*
	*	@param	(vertex)	メッシュの頂点
	*	@param	(playerPos)	プレイヤーの座標
	*	@param	(rayStart)	プレイヤーの長さ
	*	@return 当たったかどうか true : 当たった false : 当たっていない
	*/
	bool CollitionCC(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const DirectX::SimpleMath::Vector3& playerPos,
		const float& playerLength);

	/*
	*	同一平面上にいるかどうか
	*
	*	@param	(vertex)	メッシュの頂点
	*	@param	(rayStart)	レイの始点
	*	@param	(rayEnd)	レイの終点
	*	@param	(normalize)	メッシュの法線
	*	@param	(hitPoint)	当たった場所
	*	@return 含まれているかどうか	true : 含まれている false : 含まれていない
	*/
	bool OnTheSamePlane(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const DirectX::SimpleMath::Vector3& rayStart,
		const DirectX::SimpleMath::Vector3& rayEnd,
		const DirectX::SimpleMath::Vector3& normalize,
		DirectX::SimpleMath::Vector3* hitPoint);

	/*
	*	三角形の内側にいるかどうか
	*
	*	@param	(vertex)	メッシュの頂点
	*	@param	(normalize)	メッシュの法線
	*	@param	(hitPoint)	当たった場所
	*	@return 内側にいるかどうか true : 内側 false : 外側
	*/
	bool InsideTriangle(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const DirectX::SimpleMath::Vector3& normalize,
		const DirectX::SimpleMath::Vector3& hitPoint);

	/*
	*	オブジェクトとプレイヤーの距離
	*
	*	@param	(objectMesh)	オブジェクトメッシュ
	*	@return 範囲内かどうか？ true : 範囲内 false : 範囲外
	*/
	bool PlayerObjectDirection(ObjectMesh* objectMesh,
		DirectX::SimpleMath::Vector3 playerPosition, int index);

};