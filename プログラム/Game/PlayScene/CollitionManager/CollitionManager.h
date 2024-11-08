/*
* @file		CollitionManager.h
* @brief	当たり判定マネージャー
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Library/Mesh/MeshCollitionManager.h"

#include "Library/Mesh/ObjectMesh.h"

#include "BulletCollition.h"

#include "CollitionInformation.h"

#include "Game/PlayScene/Player/PlayerInformationCollition.h"

#include "Game/PlayScene/GameManager/GameManager.h"

class CollitionManager
{
public:

	//		コンストラクタ
	CollitionManager(GameManager* gameManager);

	//		デストラクタ
	~CollitionManager();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(playerInformationCollition)	インスタンスのポインタ
	*/
	void Update(PlayerInformationCollition* playerInformationCollition);

	void CollitionProcess(PlayerInformationCollition* playerInformationCollition,
		float height, int index);

	//		終了処理
	void Finalize();

private:

	//		メッシュの当たり判定
	std::unique_ptr<MeshCollitionManager> m_meshCollition;

	//		オブジェクトメッシュ
	std::vector<ObjectMesh*> m_objectMesh;
	
	//		弾の当たり判定
	std::unique_ptr<BulletCollition> m_bulletCollition;

	//		壁歩き法線
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		弾の座標
	std::vector<DirectX::SimpleMath::Vector3> m_bulletPosition;

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		当たり判定の情報
	std::unique_ptr<CollitionInformation> m_collitionInformation;

	//		ゲームマネージャーのインスタンスのポインタ
	GameManager* m_gameManager;

public:

	/*
	*	当たり判定の情報を受け取る	
	* 
	*	@return インスタンスのポインタ
	*/
	CollitionInformation* GetCollitionInformation() { return m_collitionInformation.get(); }

	/*
	*	メッシュの情報を受け取る
	* 
	*	@param	(objectMesh)	メッシュのインスタンスのポインタ
	*/
	void SetObjectMesh(std::vector<ObjectMesh*> objectMesh) { m_objectMesh = objectMesh; }

	/*
	*	壁の歩き法線を設定する
	* 
	*	@param	(normalize) 法線
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	弾の座標を設定する
	* 
	*	@param	(position)	座標
	*/
	void SetBulletPoistion(std::vector<DirectX::SimpleMath::Vector3> position) { m_bulletPosition = position; }
};