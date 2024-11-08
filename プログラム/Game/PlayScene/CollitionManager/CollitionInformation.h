/*
* @file		CollitionInformation.h
* @brief	当たり判定の情報
* @author	Morita
* @date		2024/05/16
*/

#pragma once

class CollitionInformation
{
public:

	//		コンストラクタ
	CollitionInformation();

	//		デストラクタ
	~CollitionInformation();

	//		当たり判定の情報をクリアする
	void Clear();

	/*
	*	床メッシュの情報
	* 
	*	@param	(floorHitPosition)	床に当たったポイント
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void FloorMeshInformation(
		const std::vector<DirectX::SimpleMath::Vector3>& floorhitPoint,
		const std::vector<DirectX::SimpleMath::Vector3>& floorNormalize,
		const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	壁メッシュの情報
	* 
	* 
	*/
	DirectX::SimpleMath::Vector3 WallMeshInformation(
		const std::vector<DirectX::SimpleMath::Vector2>& wallHitVelocity,
		const std::vector<DirectX::SimpleMath::Vector3>& wallHitNormalize,
		const std::vector<DirectX::SimpleMath::Vector3>& wallWalkPosition,
		const DirectX::SimpleMath::Vector3& playerPosition);

	//		終了処理
	void Finalize();

private:

	//		床に当たったポイント
	std::vector<DirectX::SimpleMath::Vector3> m_floorhitPoint;

	//		床に当たった法線
	std::vector<DirectX::SimpleMath::Vector3> m_floorNormalize;

	//		壁に当たったベロシティを受け取る
	std::vector<DirectX::SimpleMath::Vector2> m_wallHitVelocity;

	//		壁に当たった法線を受け取る
	std::vector<DirectX::SimpleMath::Vector3> m_wallHitNormalize;

	//		壁歩き時の座標
	std::vector<DirectX::SimpleMath::Vector3> m_wallWalkPosition;

	//		頭に当たっているか
	bool m_ceilingHitJudgement;
public:

	/*
	*	メッシュ床の当たったポイントを受け取る
	*
	*	@return 座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetFloorMeshHitPoint()
	{ return m_floorhitPoint; }

	/*
	*	メッシュ床の当たった法線を受け取る
	* 
	*	@return 法線
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetFloorMeshHitNormalize()
	{return m_floorNormalize;}


	/*
	*	メッシュの壁の当たったベクトルを受け取る
	*
	*	@return ベクトル
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetWallHitVelocity() { return m_wallHitVelocity; }


	/*
	*	メッシュ壁に当たった法線を受け取る
	*
	*	@return 法線
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetMeshWallNormalize() { return m_wallHitNormalize; }

	/*
	*	壁歩き時のプレイヤーの座標を受け取る
	*
	*	@return 壁歩き時のプレイヤーの座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallWalkPlayerPosition() { return m_wallWalkPosition; }

	bool GetCeilingJudgement() { return m_ceilingHitJudgement; }

	void SetCeilingJudgement(bool judgement) { m_ceilingHitJudgement = judgement; }
};
