#pragma once
#include "pch.h"

enum BonsType
{
	Body,
	BodyDown,
	LArmUp,
	LArmDown,
	LArmHand,
	RArmUp,
	RArmDown,
	RArmHand,
	LLegUp,
	LLegDown,
	LShoes,
	RLegUp,
	RLegDown,
	RShoes,
	Head,
	Gun,
	Empty,
};

struct PlayerBonsInformation
{
	//		座標
	DirectX::SimpleMath::Vector3 position;
	//		初期座標
	DirectX::SimpleMath::Vector3 firstPosition;
	//		長さ
	float length = 0.0f; 
	//		角度
	DirectX::SimpleMath::Quaternion rotation;
	//		ボーンのタイプ
	BonsType type = BonsType::Empty;
	//		親のボーン
	BonsType parent = BonsType::Empty;
};