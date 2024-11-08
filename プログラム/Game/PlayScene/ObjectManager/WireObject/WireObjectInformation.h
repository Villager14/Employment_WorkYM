/*
* @file		WireObjectInformation.h
* @brief	プレイヤーの処理
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "pch.h"

struct WireObjectInformation
{
	int number = -1;							//		番号
	DirectX::SimpleMath::Vector3 position;		//		座標
	bool m_usedJudgement = false;				//		使えるかどうか
	bool m_actionJudgement = false;				//		アクションを行っているかどうか
};