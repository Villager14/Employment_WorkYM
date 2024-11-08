
#pragma once

#include "pch.h"

struct DegitalRainParameter
{
	int number = 100000;					//		番号
	DirectX::SimpleMath::Vector3 position;	//		座標
	DirectX::SimpleMath::Matrix billbord;	//		ビルボード
	float speed = 1.0f;						//		速度
	float coolTime = 1.0f;					//		クールタイム
	float length = 0.0f;					//		距離
	float resetHeight = -10.0f;				//		消す高さ
};