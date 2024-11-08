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
	//		���W
	DirectX::SimpleMath::Vector3 position;
	//		�������W
	DirectX::SimpleMath::Vector3 firstPosition;
	//		����
	float length = 0.0f; 
	//		�p�x
	DirectX::SimpleMath::Quaternion rotation;
	//		�{�[���̃^�C�v
	BonsType type = BonsType::Empty;
	//		�e�̃{�[��
	BonsType parent = BonsType::Empty;
};