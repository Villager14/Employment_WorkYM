/*
* @file		MeshCollitionManager.h
* @brief	メッシュの当たり判定マネージャー
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Triangle.h"

#include "ObjectMesh.h"

#include "MeshCollitionFloor.h"

#include "MeshCollitionWall.h"

#include "MeshCollitionHead.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "MeshCommonProcessing.h"

class MeshCollitionManager
{
public:
	//		コンストラクタ
	MeshCollitionManager(GameManager* gameManager);

	//		デストラクタ
	~MeshCollitionManager();

	//		初期化処理
	void Initialize();

	/*
	*	メッシュの当たり判定
	*
	*	@param	(objctMesh)			オブジェクトメッシュ
	*	@param	(playerPosition)	プレイヤーの座標
	*	@param	(height)			高さ
	*	@param	(slidingJudgement)	スライディングをしているかどうか
	*	@param	(gameObject)		ゲームマネージャー
	*/
	void MeshCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		float height, bool slidingJudgement, GameManager* gameManager);


	void MeshHitPointClear();

	//		ダメージオブジェクトに当たったかどうか?
	void DamageHitJudgement();

	//		終了処理
	void Finalize();

private:

	//		プレイヤーのレイの長さ上
	const float PLAYER_ABOVE_RAY_LENGTH = 2.0f;

private:

	float playerUnderRayLength = 0.5f;

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		メッシュの当たったポイント
	std::vector<DirectX::SimpleMath::Vector3> m_meshHitPoint;

	//		壁の当たり判定
	std::vector<DirectX::SimpleMath::Vector2> m_wallHit;

	//		壁の法線の当たり判定
	std::vector<DirectX::SimpleMath::Vector3> m_wallHitNormalize;

	//		メッシュ床の当たり判定
	std::unique_ptr<MeshCollitionFloor> m_meshCollitionFloor;

	//		メッシュの壁当たり判定
	std::unique_ptr<MeshCollitionWall> m_meshCollitionWall;

	//		メッシュの頭の当たり判定
	std::unique_ptr<MeshCollitionHead> m_meshCollitionHead;

	//		壁歩き法線
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		壁歩き時のプレイヤーの座標
	std::vector<DirectX::SimpleMath::Vector3> m_wallWalkPlayerPosition;

	//		メッシュの共通処理
	std::unique_ptr<MeshCommonProcessing> m_commonProcessing;

	//		ゲームマネージャーのインスタンスのポインタ
	GameManager* m_gameManager;
public:

	/*
	*	メッシュの当たったポイントを受け取る
	*
	*	@return		座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetMeshHitPoint() { return m_meshHitPoint; }

	/*
	*	メッシュが壁に当たったポイントを受け取る
	*
	*	@return		移動量
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetMeshWallHit() { return m_wallHit; }

	/*
	*	メッシュ壁に当たった時の法線を受け取る
	*
	*	@return 法線
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallHitNormalize() { return m_wallHitNormalize; }

	/*
	*	壁の歩き法線を設定する
	*
	*	@param	(normalize) 法線
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	壁の歩き法線を受け取る
	*
	*	@return 法線
	*/
	const DirectX::SimpleMath::Vector3& GetWallWalkNormalize() { return m_wallWalkNormalize; }

	/*
	*	壁歩き時のプレイヤーの座標を受け取る
	*
	*	@return 壁歩き時のプレイヤーの座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallWalkPlayerPosition() { return m_wallWalkPlayerPosition; }

	/*
	*	床の法線を受け取る
	*
	*	@return 法線
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetFloorNormalize() { return m_meshCollitionFloor->GetNormalize(); }

	/*
	*	過去のプレイヤーの座標を設定する
	* 
	*	@param	(playerPosition)	プレイヤー座標
	*/
	void SetPastPlayerPosition(DirectX::SimpleMath::Vector3 playerPosition) {
		m_meshCollitionFloor->SetPastPlayerPosition(playerPosition);
		m_meshCollitionWall->SetPastPosition(playerPosition);
	}

	/*
	*	メッシュの共通処理を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	MeshCommonProcessing* GetCommon() { return m_commonProcessing.get(); }

	/*
	*	頭に天井が当たったかどうか？
	*	
	*	@return true : 当たっている fales : 当たっていない
	*/
	const bool GetHeadHitJudgement() { return m_meshCollitionHead->GetHitJudgement(); }
};