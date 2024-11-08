/*
*	エネミーの情報
* @brief	敵の情報
* @author	Morita
* @date		2024/08/29
*/

#pragma once

#include "pch.h"


struct EnemyInformation
{
	enum EnemyType
	{
		NormalEnemy,	//		一般エネミー

		Empty,
	};

	//		座標
	DirectX::SimpleMath::Vector3 position;

	//		視界移動時の回転量(始め)
	DirectX::SimpleMath::Quaternion startQuaternion;

	//		視界移動時の回転量(終わり)
	DirectX::SimpleMath::Quaternion endQuaternion;

	//		種類
	EnemyType enemyType = EnemyType::Empty;
};