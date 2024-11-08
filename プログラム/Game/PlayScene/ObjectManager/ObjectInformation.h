/*
*	�G�l�~�[�̏��
* @brief	�G�̏��
* @author	Morita
* @date		2024/08/29
*/

#pragma once

#include "pch.h"


struct ObjectInformation
{
	enum ObjectType
	{
		Floor,	//		���I�u�W�F�N�g

		Empty,
	};

	//		���W
	DirectX::SimpleMath::Vector3 position;

	//		��]��
	DirectX::SimpleMath::Vector3 rotation;

	//		���
	ObjectType objectType = ObjectType::Empty;

	//		���f���p�X
	std::string modelPath;

	//		�����蔻��p�X
	std::string collitionPath;

	int effectFlag;
};