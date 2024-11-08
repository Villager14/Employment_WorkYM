/*
* @file		BulletCollition.h
* @brief	弾の当たり判定
* @author	Morita
* @date		2024/05/06
*/

#pragma once

class BulletCollition
{
public:

	//		コンストラクタ
	BulletCollition();

	//		デストラクタ
	~BulletCollition();

	void Initialize();

	/*
	*	当たり判定
	*
	*	@param	(playerPosition)			プレイヤーの座標
	*	@param	(playerHeadPosition)		プレイヤーの頭の座標
	*	@param	(bulletPosition)			弾の座標
	*/	
	bool Collition(const DirectX::SimpleMath::Vector3& playerPosition,
		const DirectX::SimpleMath::Vector3& playerHeadPosition,
		const std::vector<DirectX::SimpleMath::Vector3>& bulletPosition);

private:


};