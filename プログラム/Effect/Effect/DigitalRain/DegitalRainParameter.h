
#pragma once

#include "pch.h"

struct DegitalRainParameter
{
	int number = 100000;					//		�ԍ�
	DirectX::SimpleMath::Vector3 position;	//		���W
	DirectX::SimpleMath::Matrix billbord;	//		�r���{�[�h
	float speed = 1.0f;						//		���x
	float coolTime = 1.0f;					//		�N�[���^�C��
	float length = 0.0f;					//		����
	float resetHeight = -10.0f;				//		��������
};