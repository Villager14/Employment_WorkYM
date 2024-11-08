/*
*	エネミーの情報
* @brief	敵の情報
* @author	Morita
* @date		2024/08/29
*/

#pragma once

#include "pch.h"


struct ObjectInformation
{
	enum ObjectType
	{
		Floor,	//		床オブジェクト

		Empty,
	};

	//		座標
	DirectX::SimpleMath::Vector3 position;

	//		回転量
	DirectX::SimpleMath::Vector3 rotation;

	//		種類
	ObjectType objectType = ObjectType::Empty;

	//		モデルパス
	std::string modelPath;

	//		当たり判定パス
	std::string collitionPath;

	int effectFlag;
};